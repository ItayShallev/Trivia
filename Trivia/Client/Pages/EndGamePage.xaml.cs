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
    /// Interaction logic for EndGamePage.xaml
    /// </summary>
    public partial class EndGamePage : Page
    {
        private string _username;
        private Timer _timer;
        public EndGamePage(string username)
        {
            InitializeComponent();

            secondPlaceTXT.Visibility = Visibility.Hidden;
            thirdPlaceTXT.Visibility = Visibility.Hidden;


            _timer = new Timer(UpdateResults, null, 0, 3000);
            _username = username;
        }

        private void UpdateResults(object state)
        {
            // send a game results query
            Helper.SendRequest(Constants.GetGameResultRequestId, JsonSerializer.Serialize(""));
            GetGameResultsResponse gameResultsResponse = Helper.GetResponse<GetGameResultsResponse>();

            Application.Current.Dispatcher.Invoke(
                () => // To change the UI looks, the program needs to switch to the UI thread
                {
                    List<PlayerResults> playerResults = gameResultsResponse.Results;

                    // sort the list by average answer time
                    playerResults.Sort((a, b) => a.AverageAnswerTime.CompareTo(b.AverageAnswerTime));

                    // set the 1st place text
                    PlayerResults firstPlaceResults = playerResults[0];
                    string firstPlaceTextInfo =
                        $"1st Place: {firstPlaceResults.Username} with Correct Answers / Wrong Answers: '{firstPlaceResults.CorrectAnswerCount} / {firstPlaceResults.WrongAnswerCount}' With a Total Average Time of: '{firstPlaceResults.AverageAnswerTime} seconds'";
                    firstPlaceTXT.Text = firstPlaceTextInfo;

                    if (playerResults.Count >= 3) // there are at least 3 people
                    {
                        // enable 2nd place text visibility
                        secondPlaceTXT.Visibility = Visibility.Visible;

                        // set the 2nd place text
                        PlayerResults secondPlaceResults = playerResults[1];
                        string secondPlaceTextInfo =
                            $"2nd Place: {secondPlaceResults.Username} with Correct Answers / Wrong Answers: '{secondPlaceResults.CorrectAnswerCount} / {secondPlaceResults.WrongAnswerCount}' With a Total Average Time of: '{secondPlaceResults.AverageAnswerTime} seconds'";
                        secondPlaceTXT.Text = secondPlaceTextInfo;


                        // enable 3rd place text visibility 
                        thirdPlaceTXT.Visibility = Visibility.Visible;

                        // set the 3rd place text
                        PlayerResults thirdPlaceResults = playerResults[2];
                        string thirdPlaceTextInfo =
                            $"3rd Place: {thirdPlaceResults.Username} with Correct Answers / Wrong Answers: '{thirdPlaceResults.CorrectAnswerCount} / {thirdPlaceResults.WrongAnswerCount}' With a Total Average Time of: '{thirdPlaceResults.AverageAnswerTime} seconds'";
                        thirdPlaceTXT.Text = thirdPlaceTextInfo;

                    }
                    else if (playerResults.Count >= 2)
                    {
                        // enable 2nd place text visibility
                        secondPlaceTXT.Visibility = Visibility.Visible;

                        // set 2nd place text 
                        PlayerResults secondPlaceResults = playerResults[1];
                        string secondPlaceTextInfo =
                            $"2nd Place: {secondPlaceResults.Username} with Correct Answers / Wrong Answers: '{secondPlaceResults.CorrectAnswerCount} / {secondPlaceResults.WrongAnswerCount}' With a Total Average Time of: '{secondPlaceResults.AverageAnswerTime} seconds'";
                        secondPlaceTXT.Text = secondPlaceTextInfo;
                    }
                });
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            // dispose of the timer
            _timer.Dispose();


            // Sending a Leave Game request
            Helper.SendRequest(Constants.LeaveGameRequestId,
                JsonSerializer.Serialize(new LeaveGameRequest()));
            LeaveGameResponse leaveGameResponse = Helper.GetResponse<LeaveGameResponse>();

            if (leaveGameResponse.Status == 1)
            {
                // Navigating the user back to the menu page
                MenuPage menuPage = new MenuPage(this._username);
                NavigationService.Navigate(menuPage);
            }
        }
    }
}
