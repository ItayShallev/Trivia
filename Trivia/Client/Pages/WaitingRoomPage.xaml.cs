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

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for WaitingRoomPage.xaml
    /// </summary>
    public partial class WaitingRoomPage : Page, INotifyPropertyChanged
    {
        private uint _usersCount;
        private uint _maxUsers;
        private uint RoomId { get; set; }
        private string RoomName { get; set; }
        private uint NumOfQuestionsInGame { get; set; }
        private uint TimePerQuestion { get; set; }
        private Constants.RoomState RoomState { get; set; }


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
            DataContext = this; // Set the DataContext to the current instance

            RoomId = roomData.Id;
            RoomName = roomData.Name;
            MaxUsers = roomData.MaxPlayers;
            NumOfQuestionsInGame = roomData.NumOfQuestionsInGame;
            TimePerQuestion = roomData.TimePerQuestion;
            RoomState = roomData.RoomState;

            Timer timer = new Timer(SendGetPlayersInRoomRequest, null, 0, 10000);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void UIElement_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            NavigationService.GoBack();
        }

        private void BtnStartGame_Click(object sender, RoutedEventArgs e)
        {
            if (UsersCount < MaxUsers)
            {
                ListBoxItem newUserItem = new ListBoxItem();
                newUserItem.Content = "USER " + (UsersCount + 1);

                LBUsersList.Items.Add(newUserItem);

                UsersCount++;
            }
        }

        private void SendGetPlayersInRoomRequest(object state)
        {
            // build and send the request
            string messageContent = JsonSerializer.Serialize(new GetPlayersInRoomRequest());
            string message = Helper.BuildRequest(Client.Constants.GetPlayersInRoomRequestId, messageContent);
            Communicator.Connection.SendMessage(message);

            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());
            GetPlayersInRoomResponse response = JsonSerializer.Deserialize<GetPlayersInRoomResponse>(respInfo.Message);

            UsersCount = (uint)response.Players.Count;
        }
    }
}