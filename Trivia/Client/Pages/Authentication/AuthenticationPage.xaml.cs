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


        private void BtnContinue_OnClick(object sender, RoutedEventArgs e)
        {
            // Checking if the user is known in the system before proceeding to the next page (Login / Signup)
            Helper.SendRequest(Constants.CheckIfUserExistsRequestId, JsonSerializer.Serialize(new CheckIfUserExistsRequest(UsernameTextBox.Text)));
            CheckIfUserExistsResponse checkIfUserExistsResponse = Helper.GetResponse<CheckIfUserExistsResponse>();      // Getting the server's response

            // Navigating the user to the next authentication page
            Page nextPage = (checkIfUserExistsResponse.Exists) ? new LoginPage(UsernameTextBox.Text) : new SignupPage(UsernameTextBox.Text);
            NavigationService.Navigate(nextPage);
        }
    }
}
