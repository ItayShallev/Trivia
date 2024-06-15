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
        public LeaderboardPage()
        {
            InitializeComponent();
        }

        private void LeaderboardPage_OnLoaded(object sender, RoutedEventArgs e)
        {
            // Sending GetHighScoresRequest
            Helper.SendRequest(Constants.GetHighScoreRequestId, JsonSerializer.Serialize(new GetHighScoreRequest()));
            GetHighScoreResponse getHighScoreResponse = Helper.GetResponse<GetHighScoreResponse>();

            //// get the players list from the response
            List<HighScoreRow> highScores = getHighScoreResponse.Statistics;

            // Iterating over the rows and adding entries to the leaderboard
            List<LeaderboardEntry> leaderBoardEntries = [];
            foreach (HighScoreRow highScoreRow in highScores)
            {
                LeaderboardEntry newLeaderboardEntry = new LeaderboardEntry(highScoreRow.Username,
                    highScoreRow.NumGamesPlayed, highScoreRow.NumCorrectAnswers,
                    highScoreRow.NumWrongAnswers, highScoreRow.AverageAnswerTime, highScoreRow.Points,
                    highScoreRow.Rank);

                leaderBoardEntries.Add(newLeaderboardEntry);
            }

            LeaderboardDataGrid.ItemsSource = leaderBoardEntries;
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
