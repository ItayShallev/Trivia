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
            const int NUM_MAX_PLAYERS = 5;
            
            // build and send the request
            Helper.SendRequest(Constants.GetHighScoreRequestId, "");


            ///////// TODO: DEBUG TO CHECK DESERIALIZER
            // receive the response info
            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());

            // if the response is not the wanted response
            if (respInfo.ResponseId != Constants.GetHighScoreResponseId)
            {
                // build an error list
                List<string> errorList = BuildErrorList(NUM_MAX_PLAYERS);

                // set the text elements
                //SetTxtElements(errorList);

                return;
            }

            // extract the high score response from the response info
            GetHighScoreResponse highScoreResp = JsonSerializer.Deserialize<GetHighScoreResponse>(respInfo.Message);

            // get the players list from the response
            List<string> players = highScoreResp.Statistics;

            // make sure we have the wanted amount of players
            MakeListXelements(players, NUM_MAX_PLAYERS);

            // set the txt boxes values accordingly
            //SetTxtElements(players);

        }

        private void MakeListXelements(List<string> list, int x)
        {
            if (x == list.Count) // no need to change anything
            {
                return;
            }
            else if (x > list.Count) // need to add elements
            {
                // get the number of elements that needs to be added
                int numElementsToAdd = x - list.Count;

                // add the elements
                for (int i = 0; i < numElementsToAdd; i++)
                {
                    list.Add("TBD");
                }
            }
            else // unused currently
            {
                // remove the extra elements
                list.RemoveRange(x, list.Count - x);
            }
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

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
