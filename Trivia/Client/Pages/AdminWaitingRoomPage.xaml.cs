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

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

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
            set { _roomData = value; }
        }

        public Timer Timer
        {
            get { return _timer; }
            set { _timer = value; }
        }

        public AdminWaitingRoomPage(RoomData roomData, string username)
        {
            InitializeComponent();
            DataContext = this;         // Setting the DataContext to the current instance

            RoomData = roomData;
            MaxUsers = roomData.MaxPlayers;

            Username = username;

            Timer = new Timer(UpdateUI, null, 0, 3000);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void UpdateUsersList(List<string> players)
        {
            LBUsersList.Items.Clear();      // Removing all players boxes from the players list

            // Iterating over the players list and creating a list box item for each player
            foreach (string playerName in players)
            {
                ListBoxItem newPlayerBox = new ListBoxItem { Content = playerName };
                LBUsersList.Items.Add(newPlayerBox);
            }
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
            // Sending a CloseRoom request
            Helper.SendRequest(Constants.CloseRoomRequestId, JsonSerializer.Serialize(new CloseRoomRequest(this.RoomData.Id)));
            CloseRoomResponse closeRoomResponse = Helper.GetResponse<CloseRoomResponse>();

            if (closeRoomResponse.Status == 1)
            {
                Timer.Dispose();       // Pausing the getRoomState requests from being sent to the server

                // Navigating the user back to the menu page
                MenuPage menuPage = new MenuPage(Username);
                NavigationService.Navigate(menuPage);
            }
        }

        private void BtnStartGame_Click(object sender, RoutedEventArgs e)
        {
            // Sending a start game request
            Helper.SendRequest(Constants.StartGameRequestId, JsonSerializer.Serialize(new StartGameRequest(this.RoomData.Id)));
            StartGameResponse startGameResponse = Helper.GetResponse<StartGameResponse>();

            // Checking if the server approved the start game request
            if (startGameResponse.Status == 1)
            {
                Timer.Dispose();

                // Navigating the user to the game page
                GamePage gamePage = new GamePage(Username, RoomData);
                NavigationService.Navigate(gamePage);
            }
            else
            {
                // Reinitializing the timer because the start game request failed
                Timer = new Timer(UpdateUI, null, 0, 3000);
            }
        }
    }
}
