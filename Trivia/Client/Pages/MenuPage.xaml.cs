using System;
using System.Collections.Generic;
using System.Configuration;
using System.Diagnostics;
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
using Client.ViewModels;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page
    {
        private string _username;
        private Timer _timer;

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

        public MenuPage(string username)
        {
            InitializeComponent();
            _username = username;

            // MenuPage_Loaded started the timer...

            UserGreetingTextBlock.Text = "Welcome " + this._username + "!";
        }

        private void MenuPage_OnLoaded(object sender, RoutedEventArgs e)
        {
            _timer = new Timer(UpdateUI, null, 0, 3000);
        }

        private void BtnPersonalStats_OnClick(object sender, RoutedEventArgs e)
        {
            PersonalStatsPage personalStatsPage = new PersonalStatsPage(this._username);
            _timer.Dispose();       // Pausing the getRooms requests from being sent to the server
            NavigationService.Navigate(personalStatsPage);
        }

        private void BtnLeaderboard_OnClick(object sender, RoutedEventArgs e)
        {
            LeaderboardPage leaderboardPage = new LeaderboardPage();
            _timer.Dispose();       // Pausing the getRooms requests from being sent to the server
            NavigationService.Navigate(leaderboardPage);
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomPage createRoomPage = new CreateRoomPage(Username);
            _timer.Dispose();       // Pausing the getRooms requests from being sent to the server
            NavigationService.Navigate(createRoomPage);
        }

        private void UpdateRoomsList(List<RoomData> rooms)
        {
            List<RoomEntry> roomEntries = new List<RoomEntry>();

            // Iterating over the rooms list and creating a RoomEntry item for each one
            foreach (RoomData roomData in rooms)
            {
                RoomEntry newRoomEntry = new RoomEntry(roomData.Name, roomData.Admin, roomData.RoomState.ToString(),
                    roomData.NumOfQuestionsInGame, roomData.TimePerQuestion, roomData);
                roomEntries.Add(newRoomEntry);
            }

            RoomsListDataGrid.ItemsSource = roomEntries;
        }

        private void UpdateUI(object state)
        {
            Helper.SendRequest(Constants.GetRoomsRequestId, "");
            GetRoomsResponse getRoomsResponse = Helper.GetResponse<GetRoomsResponse>();

            // Checking if there is a need to update the rooms list
            if (getRoomsResponse.Rooms.Count == RoomsListDataGrid.Items.Count) { return; }

            // Updating the rooms list UI
            Application.Current.Dispatcher.Invoke(() =>     // To change the UI looks, the program needs to switch to the UI thread
            {
                UpdateRoomsList(getRoomsResponse.Rooms);
            });
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            Helper.SendRequest(Constants.LogoutRequestId, JsonSerializer.Serialize(new LogoutRequest(Username)));
            LogoutResponse logoutResponse = Helper.GetResponse<LogoutResponse>();

            // Navigating the user back to the authentication page
            AuthenticationPage authenticationPage = new AuthenticationPage();
            NavigationService.Navigate(authenticationPage);
        }

        private void RoomClicked(object sender, SelectionChangedEventArgs e)
        {
            // Validating that the RoomClicked event handler was necessary called
            if (RoomsListDataGrid.SelectedItems.Count == 0) { return; }

            // Getting the selected room entry
            RoomEntry roomEntry = (RoomEntry)RoomsListDataGrid.SelectedItems[0];

            // Sending a join room request
            Helper.SendRequest(Constants.JoinRoomRequestId, JsonSerializer.Serialize(new JoinRoomRequest(roomEntry.RoomData.Id)));
            JoinRoomResponse joinRoomResponse = Helper.GetResponse<JoinRoomResponse>();     // Getting the server's response

            if (joinRoomResponse.Status == 1)
            {
                _timer.Dispose();       // Pausing the getRooms requests from being sent to the server
                // Navigating the user to the waiting room
                WaitingRoomPage newWaitingRoomPage = new WaitingRoomPage(roomEntry.RoomData);
                NavigationService.Navigate(newWaitingRoomPage);
            }
        }
    }
}
