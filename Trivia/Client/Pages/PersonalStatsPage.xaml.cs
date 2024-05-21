using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mime;
using System.Numerics;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
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
    /// Interaction logic for PersonalStatsPage.xaml
    /// </summary>
    public partial class PersonalStatsPage : Page
    {
        private readonly string _username;
        public PersonalStatsPage(string username)
        {
            this._username = username;
            InitializeComponent();
        }

        private void PersonalStatsPage_OnLoaded(object sender, RoutedEventArgs e)
        {
            // set the header
            UserStatsHeader.Text = _username + "'s Personal Stats";

            // build and send the request
            string message = Helper.BuildRequest(Client.Constants.GetPersonalStatsResponseId, "");
            Communicator.Connection.SendMessage(message);


            ///////// TODO: DEBUG TO CHECK DESERIALIZER
            // receive the response
            ResponseInfo respInfo  = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());
            GetPersonalStatsResponse stats = JsonSerializer.Deserialize<GetPersonalStatsResponse>(respInfo.Message);

            txtTotalScore.Text = "Total Score: " + stats.Statistics[0];
            txtGamesPlayed.Text = "Games Played: " + stats.Statistics[1];
            txtCorrectAnswers.Text = "Correct Answers: " + stats.Statistics[2];
            txtAvgAnswerTime.Text = "Average Answer Time: " + stats.Statistics[3];


        }

    }
}
