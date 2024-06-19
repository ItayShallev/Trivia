using Client.Communication;
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
using Client.ViewModels;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for LeaderboardPage.xaml
    /// </summary>
    
    public partial class LeaderboardPage : Page
    {
        public string Username { get; set; }

        public LeaderboardPage(string username)
        {
            InitializeComponent();

            Username = username;
        }

        private void LeaderboardPage_OnLoaded(object sender, RoutedEventArgs e)
        {
            AddHighScoresEntries();
        }

        private void AddHighScoresEntries()
        {
            // Sending GetHighScoresRequest
            Helper.SendRequest(Constants.GetHighScoreRequestId, JsonSerializer.Serialize(new GetHighScoreRequest()));
            GetHighScoreResponse getHighScoreResponse = Helper.GetResponse<GetHighScoreResponse>();

            List<HighScoreRow> highScores = getHighScoreResponse.Statistics;

            // Iterating over the rows and adding entries to the leaderboard
            List<LeaderboardEntry> leaderBoardEntries = [];
            bool currentUserFound = false;

            foreach (HighScoreRow highScoreRow in highScores)
            {
                if (highScoreRow.Username == Username)
                {
                    currentUserFound = true;
                }

                LeaderboardEntry newLeaderboardEntry = new LeaderboardEntry(highScoreRow.Username,
                    highScoreRow.NumGamesPlayed, highScoreRow.NumCorrectAnswers,
                    highScoreRow.NumWrongAnswers, highScoreRow.AverageAnswerTime, highScoreRow.Points,
                    highScoreRow.Rank, highScoreRow.Username == Username);

                leaderBoardEntries.Add(newLeaderboardEntry);
            }

            // Checking if the current user is in the leaderboard and adding him if not
            if (!currentUserFound)
            {
                // Sending getPersonalStats request
                Helper.SendRequest(Constants.GetPersonalStatisticsRequestId, JsonSerializer.Serialize(new GetPersonalStatisticsRequest()));
                GetPersonalStatisticsResponse getPersonalStatisticsResponse = Helper.GetResponse<GetPersonalStatisticsResponse>();

                HighScoreRow currentUserHighScoreRow = getPersonalStatisticsResponse.Statistics;

                LeaderboardEntry currentUserLeaderboardEntry = new LeaderboardEntry(currentUserHighScoreRow.Username,
                    currentUserHighScoreRow.NumGamesPlayed, currentUserHighScoreRow.NumCorrectAnswers,
                    currentUserHighScoreRow.NumWrongAnswers, currentUserHighScoreRow.AverageAnswerTime, currentUserHighScoreRow.Points,
                    currentUserHighScoreRow.Rank, true);

                // Adding the current user's statistics record to the leaderboard
                leaderBoardEntries.Add(currentUserLeaderboardEntry);
            }

            LeaderboardDataGrid.ItemsSource = leaderBoardEntries;
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
