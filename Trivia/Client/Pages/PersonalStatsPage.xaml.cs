using System;
using System.Collections;
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
            if (respInfo.ResponseId != Client.Constants.GetPersonalStatsResponseId)
            {
                // build an error list
                List<string> errorList = BuildErrorList(4);

                // set the text elements
                SetTxtElements(errorList);

                return;
            }

            // extract the personal stats from the response info
            GetPersonalStatsResponse statsResp = JsonSerializer.Deserialize<GetPersonalStatsResponse>(respInfo.Message);

            // get the personal stats 
            List<string> stats = statsResp.Statistics;

            // set the text elements
            SetTxtElements(stats);

        }

        private List<string> BuildErrorList(int numElements)
        {
            // build a new list
            List<string> errorList = new List<string>();

            // make numElements amount of error elements
            for (int i = 0; i < numElements; i++)
            {
                // add error
                errorList.Add("ERROR");
            }

            // return the error list
            return errorList;
        }


        private void SetTxtElements(List<string> txtValues)
        {
            txtTotalScore.Text = "Total Score: " + txtValues[0];
            txtGamesPlayed.Text = "Games Played: " + txtValues[1];
            txtCorrectAnswers.Text = "Correct Answers: " + txtValues[2];
            txtAvgAnswerTime.Text = "Average Answer Time: " + txtValues[3];
        }


    }
}
