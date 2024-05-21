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
    /// Interaction logic for Authentication.xaml
    /// </summary>
    public partial class AuthenticationPage : Page
    {
        public AuthenticationPage()
        {
            InitializeComponent();
        }



        //private void BtnLogin_OnClick(object sender, RoutedEventArgs e)
        //{
        //    string messageContent = JsonSerializer.Serialize(new LoginRequest(UsernameTextBox.Text, PasswordBox.Password));
        //    Communicator.Connection.SendMessage(Helper.BuildRequest(Constants.LoginRequestId, messageContent));
        //}

        //private void BtnSignup_OnClick(object sender, RoutedEventArgs e)
        //{
        //    string messageContent = JsonSerializer.Serialize(new SignupRequest(UsernameTextBox.Text, PasswordBox.Password, "Testing@gmail.com"));
        //    Communicator.Connection.SendMessage(Helper.BuildRequest(Constants.SignupRequestId, messageContent));
        //}
        private void BtnContinue_OnClick(object sender, RoutedEventArgs e)
        {
            // Redirecting the user to the LoginPage or to the SignupPage depending if the user exists on the DB

            string messageContent = JsonSerializer.Serialize(new CheckIfUserExistsRequest(UsernameTextBox.Text));
            Communicator.Connection.SendMessage(Helper.BuildRequest(Constants.CheckIfUserExistsRequestId, messageContent));

            ResponseInfo responseInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());

            // Checking the response code
            if (responseInfo.ResponseId == Constants.CheckIfUserExistsResponseId)           // If the server returned valid response...
            {
                CheckIfUserExistsResponse response = JsonSerializer.Deserialize<CheckIfUserExistsResponse>(responseInfo.Message);

                if (response.Exists)
                {
                    LoginPage loginPage = new LoginPage();
                    NavigationService.Navigate(loginPage);
                }
                else
                {
                    SignupPage signupPage = new SignupPage();
                    NavigationService.Navigate(signupPage);
                }
            }
            else if (responseInfo.ResponseId == Constants.CheckIfUserExistsResponseId)      // If the server returned an Error...
            {
                throw new Exception(responseInfo.Message);
            }
        }
    }
}
