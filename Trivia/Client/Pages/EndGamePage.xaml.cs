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
using Client.ViewModels;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for EndGamePage.xaml
    /// </summary>
    public partial class EndGamePage : Page
    {
        private string _username;
        private RoomData _roomData;
        private Timer _timer;
        private uint _usersCount;


        public EndGamePage(string username, RoomData roomData, uint usersCount)
        {
            InitializeComponent();

            _timer = new Timer(UpdateUI, null, 0, 3000);
            _username = username;
            _roomData = roomData;
            _usersCount = usersCount;
        }

        private bool IsResultsListUpdateNeeded(List<PlayerResults> playerResults)
        {
            // To prevent users from being removed from the results list when they leave the game
            if (playerResults.Count != ResultsDataGrid.Items.Count)
            {
                // If all users have a Result record in the list - stopping to update the list due to a change in the users count
                return ResultsDataGrid.Items.Count != _usersCount;
            }

            List<GameResultsEntry> gameResultEntries = ResultsDataGrid.ItemsSource as List<GameResultsEntry>;

            // Iterating over the results list and comparing it to the one that the server responded with
            for (int i = 0; ((i < gameResultEntries.Count) && (i < playerResults.Count)); i++)
            {
                // Checking if some info changed in the current game result
                if (gameResultEntries[i].NumCorrectAnswers != playerResults[i].CorrectAnswerCount ||
                    gameResultEntries[i].NumWrongAnswers != playerResults[i].WrongAnswerCount ||
                    Math.Abs(gameResultEntries[i].AverageAnswerTime - playerResults[i].AverageAnswerTime) > Constants.FLOAT_DIFFERENCE_TOLERANCE ||
                    gameResultEntries[i].Points != playerResults[i].Points)
                {
                    return true;
                }
            }

            return false;
        }

        private void UpdateResults(List<PlayerResults> playerResults)
        {
            List<GameResultsEntry> gameResultsEntries = [];

            // Iterating over the rooms list and creating a RoomEntry item for each one
            foreach (PlayerResults playerResult in playerResults)
            {
                GameResultsEntry newGameResultsEntry = new GameResultsEntry(playerResult.Username, playerResult.CorrectAnswerCount,
                    playerResult.WrongAnswerCount, playerResult.AverageAnswerTime, playerResult.Points, playerResult.Rank, playerResult.Username == _username);
                gameResultsEntries.Add(newGameResultsEntry);
            }

            ResultsDataGrid.ItemsSource = gameResultsEntries;
        }

        private void UpdateUI(object state)
        {
            // send a game results query
            Helper.SendRequest(Constants.GetGameResultRequestId, JsonSerializer.Serialize(new GetGameResultsRequest()));
            GetGameResultsResponse getGameResultsResponse = Helper.GetResponse<GetGameResultsResponse>();

            if (IsResultsListUpdateNeeded(getGameResultsResponse.Results))
            {
                // Updating the results list UI
                Application.Current.Dispatcher.Invoke(() =>     // To change the UI looks, the program needs to switch to the UI thread
                {
                    UpdateResults(getGameResultsResponse.Results);
                });
            }
        }

        private void BtnWaitingRoom_OnClick(object sender, RoutedEventArgs e)
        {
            // dispose of the timer
            _timer.Dispose();

            // Sending a Leave Game request
            Helper.SendRequest(Constants.LeaveGameRequestId,
                JsonSerializer.Serialize(new LeaveGameRequest()));
            LeaveGameResponse leaveGameResponse = Helper.GetResponse<LeaveGameResponse>();

            if (leaveGameResponse.Status == 1)
            {
                if (_username == _roomData.Admin)       // If the user is the admin of the room
                {
                    AdminWaitingRoomPage adminWaitingRoomPage = new AdminWaitingRoomPage(_roomData, _username);
                    NavigationService.Navigate(adminWaitingRoomPage);
                }
                else                                    // If the user is a regular member in the room
                {
                    MemberWaitingRoomPage memberWaitingRoomPage = new MemberWaitingRoomPage(_roomData, _username);
                    NavigationService.Navigate(memberWaitingRoomPage);
                }
            }
        }
    }
}
