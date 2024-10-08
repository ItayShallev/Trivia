﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Configuration;
using System.Diagnostics;
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
using Client.ViewModels;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page, INotifyPropertyChanged
    {
        private string _username;
        private Timer _timer;


        public string Username
        {
            get { return _username; }
            set
            {
                if (_username != value)
                {
                    _username = value;
                    OnPropertyChanged();
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


        public MenuPage(string username)
        {
            InitializeComponent();
            DataContext = this;

            Username = username;

            // MenuPage_Loaded started the timer...
        }

        private void MenuPage_OnLoaded(object sender, RoutedEventArgs e)
        {
            _timer = new Timer(UpdateUI, null, 0, Constants.REQUEST_INTERVAL);
        }

        private void BtnLeaderboard_OnClick(object sender, RoutedEventArgs e)
        {
            _timer.Dispose();       // Pausing the getRooms requests from being sent to the server

            LeaderboardPage leaderboardPage = new LeaderboardPage(Username);
            NavigationService.Navigate(leaderboardPage);
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            _timer.Dispose();       // Pausing the getRooms requests from being sent to the server

            CreateRoomPage createRoomPage = new CreateRoomPage(Username);
            NavigationService.Navigate(createRoomPage);
        }

        private bool IsRoomsListUpdateNeeded(List<RoomData> rooms)
        {
            // If a room was added
            if (rooms.Count != RoomsListDataGrid.Items.Count)
            {
                return true;
            }

            if (rooms.Count != 0)      // If the room count isn't 0
            {
                List<RoomEntry> roomEntries = RoomsListDataGrid.ItemsSource as List<RoomEntry>;     // The rooms that appear on the rooms list

                // Iterating over the GUI rooms list comparing it to the one that the server responded with
                for (int i = 0; ((i < roomEntries.Count) && (i < rooms.Count)); i++)
                {
                    // Checking if some room status has changed
                    if (Helper.StringStatusToRoomStatus(roomEntries[i].RoomStatus) != rooms[i].RoomStatus)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
        private void UpdateRoomsList(List<RoomData> rooms)
        {
            List<RoomEntry> roomEntries = new List<RoomEntry>();

            // Iterating over the rooms list and creating a RoomEntry item for each one
            foreach (RoomData roomData in rooms)
            {
                if (roomData.RoomStatus == Constants.RoomStatus.Waiting || roomData.RoomStatus == Constants.RoomStatus.Full)
                {
                    RoomEntry newRoomEntry = new RoomEntry(roomData.Name, roomData.Admin,
                        Helper.RoomStatusToStringStatus(roomData.RoomStatus),
                        roomData.NumOfQuestionsInGame, roomData.TimePerQuestion, roomData);
                    roomEntries.Add(newRoomEntry);
                }
            }

            RoomsListDataGrid.ItemsSource = roomEntries;
        }

        private void UpdateUI(object state)
        {
            Helper.SendRequest(Constants.GetRoomsRequestId, JsonSerializer.Serialize(new GetRoomsRequest()));
            GetRoomsResponse getRoomsResponse = Helper.GetResponse<GetRoomsResponse>();

            // Checking if there is a need to update the rooms list
            if (IsRoomsListUpdateNeeded(getRoomsResponse.Rooms))
            {
                // Updating the rooms list UI
                Application.Current.Dispatcher.Invoke(() =>     // To change the UI looks, the program needs to switch to the UI thread
                {
                    UpdateRoomsList(getRoomsResponse.Rooms);
                });
            }
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            Helper.SendRequest(Constants.LogoutRequestId, JsonSerializer.Serialize(new LogoutRequest(Username)));
            LogoutResponse logoutResponse = Helper.GetResponse<LogoutResponse>();

            _timer.Dispose();       // Pausing the getRooms requests from being sent to the server

            // Navigating the user back to the authentication page
            AuthenticationPage authenticationPage = new AuthenticationPage();
            NavigationService.Navigate(authenticationPage);
        }

        private void RoomClicked(object sender, SelectionChangedEventArgs e)
        {
            // Validating that the RoomClicked event handler was necessary called
            if (RoomsListDataGrid.SelectedItems.Count == 0) { return; }

            // Getting the selected room entry
            RoomEntry roomEntry = RoomsListDataGrid.SelectedItems[0] as RoomEntry;

            // Sending a join room request
            Helper.SendRequest(Constants.JoinRoomRequestId, JsonSerializer.Serialize(new JoinRoomRequest(roomEntry.RoomData.Id)));
            JoinRoomResponse joinRoomResponse = Helper.GetResponse<JoinRoomResponse>();     // Getting the server's response

            if (joinRoomResponse.Status == 1)
            {
                _timer.Dispose();       // Pausing the getRooms requests from being sent to the server
                // Navigating the user to the member waiting room
                MemberWaitingRoomPage memberWaitingRoomPage = new MemberWaitingRoomPage(roomEntry.RoomData, Username);
                NavigationService.Navigate(memberWaitingRoomPage);
            }
        }
    }
}
