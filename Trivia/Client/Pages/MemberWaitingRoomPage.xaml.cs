using Client.Communication;
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
            set
            {
                _roomData = value;
            }
        }


        public MemberWaitingRoomPage(RoomData roomData, string username)
        {
            InitializeComponent();
            DataContext = this;         // Setting the DataContext to the current instance (to display the current user's data on xaml page)

            RoomData = roomData;
            MaxUsers = roomData.MaxPlayers;

            Username = username;

            _timer = new Timer(UpdateUI, null, 0, 3000);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void LeaveRoom()
        {
            // Sending a LeaveRoom request
            Helper.SendRequest(Constants.LeaveRoomRequestId, JsonSerializer.Serialize(new LeaveRoomRequest()));
            LeaveRoomResponse leaveRoomResponse = Helper.GetResponse<LeaveRoomResponse>();

            if (leaveRoomResponse.Status == 1)
            {
                _timer.Dispose();       // Pausing the getRoomState requests from being sent to the server

                // Navigating the user back to the menu page
                MenuPage menuPage = new MenuPage(Username);
                NavigationService.Navigate(menuPage);
            }
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
                // Checking if the room status has changed
                if (getRoomStateResponse.RoomStatus == Constants.RoomStatus.Closed)     // Checking if the admin closed the room
                {
                    LeaveRoom();
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
