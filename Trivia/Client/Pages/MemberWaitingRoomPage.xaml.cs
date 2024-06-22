using Client.Communication;
using Client.ViewModels;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
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

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for MemberWaitingRoomPage.xaml
    /// </summary>
    public partial class MemberWaitingRoomPage : Page, INotifyPropertyChanged
    {
        private string _username;
        private uint _usersCount;
        private uint _maxUsers;
        private RoomData _roomData;
        private Timer _timer;

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


        public MemberWaitingRoomPage(RoomData roomData, string username)
        {
            InitializeComponent();
            DataContext = this;         // Setting the DataContext to the current instance (to display the current user's data on xaml page)

            RoomData = roomData;
            MaxUsers = roomData.MaxPlayers;

            _username = username;

            _timer = new Timer(UpdateUI, null, 0, Constants.REQUEST_INTERVAL);
        }

        private void LeaveRoom()
        {
            _timer.Dispose();       // Pausing the getRoomState requests from being sent to the server
            
            // Sending a LeaveRoom request
            Helper.SendRequest(Constants.LeaveRoomRequestId, JsonSerializer.Serialize(new LeaveRoomRequest()));
            LeaveRoomResponse leaveRoomResponse = Helper.GetResponse<LeaveRoomResponse>();

            if (leaveRoomResponse.Status == 1)
            {
                // Navigating the user back to the menu page
                MenuPage menuPage = new MenuPage(_username);
                NavigationService.Navigate(menuPage);
            }
        }

        private void UpdateUsersList(List<string> users)
        {
            List<UserEntry> userEntries = new List<UserEntry>();

            // Iterating over the users list and creating a UserEntry item for each one
            foreach (string user in users)
            {
                UserEntry newUserEntry = new UserEntry(user, user == RoomData.Admin, user == _username);
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
                // Checking if the room status has changed
                if (getRoomStateResponse.RoomStatus == Constants.RoomStatus.Closed)     // Checking if the admin closed the room
                {
                    LeaveRoom();
                }
                else if (getRoomStateResponse.RoomStatus == Constants.RoomStatus.Playing)
                {
                    _timer.Dispose();

                    GamePage gamePage = new GamePage(_username, RoomData, UsersCount);
                    NavigationService.Navigate(gamePage);
                }
                else if (UsersCount != getRoomStateResponse.Players.Count)
                {
                    UpdateUsersList(getRoomStateResponse.Players);
                    UsersCount = (uint)getRoomStateResponse.Players.Count;
                }
            });
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            LeaveRoom();
        }
    }
}
