using Client.Communication;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Net;
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
using System.Windows.Threading;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class GamePage : Page, INotifyPropertyChanged
    {
        static Random rnd = new Random();


        private string Username { get; set; }
        public RoomData RoomData { get; set; }

        private DispatcherTimer QuestionTimer { get; set; }
        private double _timeElapsed;

        public double TimeElapsed
        {
            get { return _timeElapsed; }
            set
            {
                if (_timeElapsed != value)
                {
                    _timeElapsed = value;
                    OnPropertyChanged();
                }
            }
        }


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
                QuestionTextBlock.Text = WebUtility.HtmlDecode(getQuestionResponse.Question);

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

                StartTimer();
            }
            else
            {
                // Navigating the user to the results page
                //////////////////////////////////////////
            }
        }

        private void StartTimer()
        {
            // Clearing the old timer if it already exists
            if (QuestionTimer != null)
            {
                QuestionTimer.Stop();
                QuestionTimer.Tick -= Timer_Tick;
                QuestionTimer = null;
            }

            QuestionTimer = new DispatcherTimer();
            QuestionTimer.Interval = TimeSpan.FromSeconds(0.1);
            QuestionTimer.Tick += Timer_Tick;
            TimeElapsed = 0;
            QuestionTimer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            TimeElapsed += 0.1;
        }


        private void SetIsEnabledPropertyForAnswerButtons(bool value)
        {
            ButtonAnswer0.IsHitTestVisible = value;
            ButtonAnswer1.IsHitTestVisible = value;
            ButtonAnswer2.IsHitTestVisible = value;
            ButtonAnswer3.IsHitTestVisible = value;
        }



        private async void SubmitAnswer(object sender, RoutedEventArgs e)
        {
            // Disabling all answer buttons
            SetIsEnabledPropertyForAnswerButtons(false);

            Button pressedButton = sender as Button;
            uint userAnswerId = (uint)pressedButton.Tag;

            Helper.SendRequest(Constants.SubmitAnswerRequestId, JsonSerializer.Serialize(new SubmitAnswerRequest(userAnswerId, TimeElapsed)));
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

            // Enabling the answer buttons
            SetIsEnabledPropertyForAnswerButtons(true);
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

        public event PropertyChangedEventHandler? PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string? propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
