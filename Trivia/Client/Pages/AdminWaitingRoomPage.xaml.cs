using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection.Metadata;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Client.Communication;
using Client.UserControls;
using Client.ViewModels;
using static Client.Constants;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for AdminWaitingRoomPage.xaml
    /// </summary>
    public partial class AdminWaitingRoomPage : Page, INotifyPropertyChanged
    {
        private string _username;
        private uint _usersCount;
        private uint _maxUsers;
        private RoomData _roomData;
        private Timer _timer;


        // Properties (for live UI updates)
        public uint UsersCount
        {
            get { return _usersCount; }
            set
            {
                if (_usersCount != value)
                {
                    _usersCount = value;
                    OnPropertyChanged();
                }
            }
        }

        public uint MaxUsers
        {
            get { return _maxUsers; }
            set
            {
                if (_maxUsers != value)
                {
                    _maxUsers = value;
                    OnPropertyChanged();
                }
            }
        }

        public RoomData RoomData
        {
            get { return _roomData; }
            set
            {
                _roomData = value;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


        public AdminWaitingRoomPage(RoomData roomData, string username)
        {
            InitializeComponent();
            DataContext = this;         // Setting the DataContext to the current instance

            _roomData = roomData;
            MaxUsers = roomData.MaxPlayers;

            _username = username;

            _timer = new Timer(UpdateUI, null, 0, Constants.REQUEST_INTERVAL);
        }

        private void UpdateUsersList(List<string> users)
        {
            List<UserEntry> userEntries = new List<UserEntry>();

            // Iterating over the users list and creating a UserEntry item for each one
            foreach (string user in users)
            {
                UserEntry newUserEntry = new UserEntry(user, user == _roomData.Admin, user == _username);
                userEntries.Add(newUserEntry);
            }

            UsersListDataGrid.ItemsSource = userEntries;
        }

        private void UpdateUI(object state)
        {
            // Sending a request to get the room state
            Helper.SendRequest(Constants.GetRoomStateRequestId, JsonSerializer.Serialize(new GetRoomStateRequest()));

            // Getting the response from the server
            GetRoomStateResponse getRoomStateResponse = Helper.GetResponse<GetRoomStateResponse>();

            // Updating the waiting room UI
            Application.Current.Dispatcher.Invoke(() =>     // To change the UI looks, the program needs to switch to the UI thread
            {
                if (UsersCount != getRoomStateResponse.Players.Count)
                {
                    UpdateUsersList(getRoomStateResponse.Players);
                    UsersCount = (uint)getRoomStateResponse.Players.Count;
                }
            });
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            _timer.Dispose();       // Pausing the getRoomState requests from being sent to the server
            
            // Sending a CloseRoom request
            Helper.SendRequest(Constants.CloseRoomRequestId, JsonSerializer.Serialize(new CloseRoomRequest(_roomData.Id)));
            CloseRoomResponse closeRoomResponse = Helper.GetResponse<CloseRoomResponse>();

            if (closeRoomResponse.Status == 1)
            {
                // Navigating the user back to the menu page
                MenuPage menuPage = new MenuPage(_username);
                NavigationService.Navigate(menuPage);
            }
        }

        private void BtnStartGame_Click(object sender, RoutedEventArgs e)
        {
            // Sending a start game request
            Helper.SendRequest(Constants.StartGameRequestId, JsonSerializer.Serialize(new StartGameRequest(_roomData.Id)));
            StartGameResponse startGameResponse = Helper.GetResponse<StartGameResponse>();

            // Checking if the server approved the start game request
            if (startGameResponse.Status == 1)
            {
                _timer.Dispose();

                // Navigating the user to the game page
                GamePage gamePage = new GamePage(_username, _roomData, UsersCount);
                NavigationService.Navigate(gamePage);
            }
        }
    }
}
