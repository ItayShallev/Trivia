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
using System.Web;
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
        private int AnswersCount { get; set; }
        public RoomData RoomData { get; set; }
        public uint UsersCount { get; set; }

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


        public GamePage(string username, RoomData roomData, uint userCount)
        {
            InitializeComponent();

            Username = username;
            RoomData = roomData;
            UsersCount = userCount;

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
                QuestionTextBlock.Text = Helper.DecodeAsciiCodes(getQuestionResponse.Question);

                // Setting the question difficulty
                DifficultyTextBlock.Text = Helper.QuestionDifficultyToStringDifficulty(getQuestionResponse.Difficulty);

                // Setting the possible answers in random order
                int[] arr = new int[] { 0, 1, 2, 3 };
                rnd.Shuffle(arr);

                Answer0TextBlock.Text = Helper.DecodeAsciiCodes(getQuestionResponse.Answers[arr[0]].Answer);
                ButtonAnswer0.Tag = getQuestionResponse.Answers[arr[0]].AnswerId;

                Answer1TextBlock.Text = Helper.DecodeAsciiCodes(getQuestionResponse.Answers[arr[1]].Answer);
                ButtonAnswer1.Tag = getQuestionResponse.Answers[arr[1]].AnswerId;

                Answer2TextBlock.Text = Helper.DecodeAsciiCodes(getQuestionResponse.Answers[arr[2]].Answer);
                ButtonAnswer2.Tag = getQuestionResponse.Answers[arr[2]].AnswerId;

                Answer3TextBlock.Text = Helper.DecodeAsciiCodes(getQuestionResponse.Answers[arr[3]].Answer);
                ButtonAnswer3.Tag = getQuestionResponse.Answers[arr[3]].AnswerId;

                StartTimer();
            }
        }

        private void StopTimer()
        {
            if (QuestionTimer != null)
            {
                QuestionTimer.Stop();
                QuestionTimer.Tick -= Timer_Tick;
                QuestionTimer = null;
            }
        }

        private void StartTimer()
        {
            // Clearing the old timer if it already exists
            StopTimer();

            QuestionTimer = new DispatcherTimer();
            QuestionTimer.Interval = TimeSpan.FromSeconds(0.1);
            QuestionTimer.Tick += Timer_Tick;
            TimeElapsed = 0;
            QuestionTimer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            TimeElapsed += 0.1;

            // Checking if the time is up
            if (TimeElapsed >= RoomData.TimePerQuestion - 0.1)
            {
                QuestionTimer.Stop();

                TimeElapsed = RoomData.TimePerQuestion;     // To avoid some inaccuracies of the Stopwatch

                SubmitAnswer(Constants.TIME_EXPIRED_ANSWER_ID, null);
            }
        }


        private void SetIsEnabledPropertyForAnswerButtons(bool value)
        {
            ButtonAnswer0.IsHitTestVisible = value;
            ButtonAnswer1.IsHitTestVisible = value;
            ButtonAnswer2.IsHitTestVisible = value;
            ButtonAnswer3.IsHitTestVisible = value;
        }

        private async void SubmitAnswer(uint userAnswerId, Button? pressedButton)
        {
            // Disabling all answer buttons
            SetIsEnabledPropertyForAnswerButtons(false);

            Helper.SendRequest(Constants.SubmitAnswerRequestId, JsonSerializer.Serialize(new SubmitAnswerRequest(userAnswerId, TimeElapsed)));
            SubmitAnswerResponse submitAnswerResponse = Helper.GetResponse<SubmitAnswerResponse>();

            // Changing the pressed button color
            if (pressedButton != null)
            {
                if (submitAnswerResponse.CorrectAnswerId == userAnswerId)
                {
                    pressedButton.Background = new SolidColorBrush(Colors.Green);
                }
                else
                {
                    pressedButton.Background = new SolidColorBrush(Colors.Red);
                }
            }
            else
            {
                ButtonAnswer0.Background = new SolidColorBrush(Colors.Red);
                ButtonAnswer1.Background = new SolidColorBrush(Colors.Red);
                ButtonAnswer2.Background = new SolidColorBrush(Colors.Red);
                ButtonAnswer3.Background = new SolidColorBrush(Colors.Red);
            }

            // Incrementing the answers count
            AnswersCount++;

            // Waiting a second to let the user see if his answer is correct or incorrect
            await Task.Delay(1000);

            // Resetting the buttons' colors
            ButtonAnswer0.Background = new SolidColorBrush(Colors.DodgerBlue);
            ButtonAnswer1.Background = new SolidColorBrush(Colors.DodgerBlue);
            ButtonAnswer2.Background = new SolidColorBrush(Colors.DodgerBlue);
            ButtonAnswer3.Background = new SolidColorBrush(Colors.DodgerBlue);

            // Checking if there are more questions for the user
            if (AnswersCount < RoomData.NumOfQuestionsInGame)
            {
                // Displaying the next question
                DisplayNextQuestion();

                // Enabling the answer buttons
                SetIsEnabledPropertyForAnswerButtons(true);
            }
            else // there are no more questions for the user
            {
                // go to the end game page 
                EndGamePage endgamePage = new EndGamePage(this.Username, RoomData, UsersCount);
                NavigationService.Navigate(endgamePage);
            }
        }


        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {

            // Sending a Leave Game request
            Helper.SendRequest(Constants.LeaveGameRequestId,
                JsonSerializer.Serialize(new LeaveGameRequest()));
            LeaveGameResponse leaveGameResponse = Helper.GetResponse<LeaveGameResponse>();

            if (leaveGameResponse.Status == 1)
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

        private async void ButtonAnswer_OnClick(object sender, RoutedEventArgs e)
        {
            // Stopping the timer
            StopTimer();

            Button pressedButton = sender as Button;
            uint userAnswerId = (uint)pressedButton.Tag;

            SubmitAnswer(userAnswerId, pressedButton);
        }
    }
}
