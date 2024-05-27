using System;
using System.Collections.Generic;
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

        private void BtnPersonalStats_Click(object sender, RoutedEventArgs e)
        {
            PersonalStatsPage personalStatsPage = new PersonalStatsPage(this._username);
            NavigationService.Navigate(personalStatsPage);
        }

        private void BtnLeaderboard_Click(object sender, RoutedEventArgs e)
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
            //// build and send the request
            //string message = Helper.BuildRequest(Client.Constants., "");
            //Communicator.Connection.SendMessage(message);


            /////////// TODO: DEBUG TO CHECK DESERIALIZER
            //// receive the response info
            //ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());
            List<RoomData> rooms = new List<RoomData>()
            {
                new RoomData(1, "Room1", 5, 5, 5, Constants.RoomState.Waiting),
                new RoomData(2, "Room2", 5, 5, 5, Constants.RoomState.Waiting),
                new RoomData(3, "Room3", 5, 5, 5, Constants.RoomState.Waiting),
                new RoomData(4, "Room4", 5, 5, 5, Constants.RoomState.Waiting),
                new RoomData(5, "Room5", 5, 5, 5, Constants.RoomState.Waiting)
            };
            foreach (RoomData room in rooms)
            {
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
            RoomData room = (RoomData)(((TextBlock)sender).Tag);
            
        }
    }
}
