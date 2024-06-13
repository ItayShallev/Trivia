using Client.Communication;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
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
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class GamePage : Page
    {
        static Random rnd = new Random();


        private string Username { get; set; }
        private RoomData RoomData { get; set; }
        // GameData ????


        public GamePage(string username, RoomData roomData)
        {
            InitializeComponent();

            Username = username;
            RoomData = roomData;

            DisplayNextQuestion();
        }

        private void DisplayNextQuestion()
        {
            Helper.SendRequest(Constants.GetQuestionRequestId, JsonSerializer.Serialize(new GetQuestionRequest()));
            GetQuestionResponse getQuestionResponse = Helper.GetResponse<GetQuestionResponse>();

            // Displaying the starting question on the screen
            if (getQuestionResponse.Status == 1)
            {
                // Setting the question
                QuestionTextBlock.Text = getQuestionResponse.Question;

                // Setting the possible answers in random order
                int[] arr = new int[] { 0, 1, 2, 3 };
                rnd.Shuffle(arr);
                
                ButtonAnswer0.Content = getQuestionResponse.Answers[arr[0]].Answer;
                ButtonAnswer0.Tag = getQuestionResponse.Answers[arr[0]].AnswerId;

                ButtonAnswer1.Content = getQuestionResponse.Answers[arr[1]].Answer;
                ButtonAnswer1.Tag = getQuestionResponse.Answers[arr[1]].AnswerId;

                ButtonAnswer2.Content = getQuestionResponse.Answers[arr[2]].Answer;
                ButtonAnswer2.Tag = getQuestionResponse.Answers[arr[2]].AnswerId;

                ButtonAnswer3.Content = getQuestionResponse.Answers[arr[3]].Answer;
                ButtonAnswer3.Tag = getQuestionResponse.Answers[arr[3]].AnswerId;
            }
            else
            {
                // Navigating the user to the results page
                //////////////////////////////////////////
            }
        }

        private async void SubmitAnswer(object sender, RoutedEventArgs e)
        {
            Button pressedButton = sender as Button;
            uint userAnswerId = (uint)pressedButton.Tag;

            Helper.SendRequest(Constants.SubmitAnswerRequestId, JsonSerializer.Serialize(new SubmitAnswerRequest(userAnswerId, 5.2)));
            SubmitAnswerResponse submitAnswerResponse = Helper.GetResponse<SubmitAnswerResponse>();

            if (submitAnswerResponse.CorrectAnswerId == userAnswerId)
            {
                pressedButton.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                pressedButton.Background = new SolidColorBrush(Colors.Red);
            }

            // Waiting a second to let the user see if his answer is correct or incorrect
            await Task.Delay(1000);

            // Resetting the buttons' colors
            pressedButton.Background = new SolidColorBrush(Colors.DodgerBlue);
            
            // Displaying the next question
            DisplayNextQuestion();
        }


        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            // Sending a CloseRoom request
            Helper.SendRequest(Constants.CloseRoomRequestId, JsonSerializer.Serialize(new CloseRoomRequest(this.RoomData.Id)));
            CloseRoomResponse closeRoomResponse = Helper.GetResponse<CloseRoomResponse>();

            if (closeRoomResponse.Status == 1)
            {
                // Navigating the user back to the menu page
                MenuPage menuPage = new MenuPage(Username);
                NavigationService.Navigate(menuPage);
            }
        }
    }
}
