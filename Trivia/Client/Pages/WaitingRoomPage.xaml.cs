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
using Client.Communication;
using static Client.Constants;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for WaitingRoomPage.xaml
    /// </summary>
    public partial class WaitingRoomPage : Page, INotifyPropertyChanged
    {
        private uint _usersCount;
        private uint _maxUsers;
        private RoomData _roomData;
        private Timer _timer;

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

        public WaitingRoomPage(RoomData roomData)
        {
            InitializeComponent();
            DataContext = this;         // Setting the DataContext to the current instance

            this._roomData = roomData;
            MaxUsers = roomData.MaxPlayers;

            _timer = new Timer(UpdateUI, null, 0, 3000);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void UIElement_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            // Leave Room
            NavigationService.GoBack();
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
            // Sending a request to get the list of players in the room
            Helper.SendRequest(Constants.GetPlayersInRoomRequestId, JsonSerializer.Serialize(new GetPlayersInRoomRequest()));

            // Getting the response from the server
            GetPlayersInRoomResponse response = Helper.GetResponse<GetPlayersInRoomResponse>();

            // Updating the users list and users count
            Application.Current.Dispatcher.Invoke(() =>     // To change the UI looks, the program needs to switch to the UI thread
            {
                if (UsersCount != response.Players.Count)
                {
                    UpdateUsersList(response.Players);
                    UsersCount = (uint)response.Players.Count;
                }
            });
        }
    }
}