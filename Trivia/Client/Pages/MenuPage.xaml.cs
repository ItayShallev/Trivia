using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
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
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page
    {
        private string _username;

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

        public MenuPage(string username)
        {
            InitializeComponent();
            _username = username;

            UserGreetingTextBlock.Text = "Welcome " + this._username + "!";
        }

        private void BtnPersonalStats_OnClick(object sender, RoutedEventArgs e)
        {
            PersonalStatsPage personalStatsPage = new PersonalStatsPage(this._username);
            NavigationService.Navigate(personalStatsPage);
        }

        private void BtnLeaderboard_OnClick(object sender, RoutedEventArgs e)
        {
            LeaderboardPage leaderboardPage = new LeaderboardPage();
            NavigationService.Navigate(leaderboardPage);
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomPage createRoomPage = new CreateRoomPage();
            NavigationService.Navigate(createRoomPage);
        }

        private void MenuPage_OnLoaded(object sender, RoutedEventArgs e)
        {
            // build and send the request
            Helper.SendRequest(Constants.GetRoomsRequestId, "");


            ///////// TODO: DEBUG TO CHECK DESERIALIZER
            // receive the response info
            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());

            // if the response id is not the expected one
            if (respInfo.ResponseId != Constants.GetRoomsResponseId)
            {
                // enable the error header and show the error
                txtErrorHeader.Text = "ERROR WITH GET ROOMS REQUEST";
                txtErrorHeader.Visibility = Visibility.Visible;
                return;
            }

            // get the rooms response
            GetRoomsResponse roomsResp = JsonSerializer.Deserialize<GetRoomsResponse>(respInfo.Message);

            // get the rooms
            List<RoomData> rooms = roomsResp.Rooms;


            foreach (RoomData room in rooms)
            {
                // add a room to the list
                TextBlock txtBlock = new TextBlock();
                txtBlock.Text = room.Name;
                txtBlock.Tag = room;
                txtBlock.Height = 50;
                txtBlock.Width = 300;
                txtBlock.MouseLeftButtonDown += TxtBlock_MouseLeftButtonDown;
                lstRoomList.Items.Add(txtBlock);
            }

        }

        private void TxtBlock_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            RoomData room = (RoomData)((TextBlock)sender).Tag;

            // Sending a join room request
            Helper.SendRequest(Constants.JoinRoomRequestId, JsonSerializer.Serialize(new JoinRoomRequest(room.Id)));
            JoinRoomResponse joinRoomResponse = Helper.GetResponse<JoinRoomResponse>();

            // Navigating the user to the waiting room
            WaitingRoomPage newWaitingRoomPage = new WaitingRoomPage(room);
            NavigationService.Navigate(newWaitingRoomPage);
        }
    }
}
