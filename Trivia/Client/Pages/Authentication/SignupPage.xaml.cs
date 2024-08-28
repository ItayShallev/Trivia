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
    /// Interaction logic for SignupPage.xaml
    /// </summary>
    public partial class SignupPage : Page
    {
        private string _username;

        public SignupPage(string username)
        {
            this._username = username;
            InitializeComponent();

            // Focusing on the password box
            pswdPasswordBox.Focus();
        }

        private void BtnSignup_OnClick(object sender, RoutedEventArgs e)
        {
            // Sending a signup request to the server
            Helper.SendRequest(Constants.SignupRequestId, JsonSerializer.Serialize(new SignupRequest(this._username, pswdPasswordBox.Password, txtMail.Text)));

            // receive the response
            SignupResponse signupResponse = Helper.GetResponse<SignupResponse>();

            if (signupResponse.Status == 1)
            {
                MenuPage menuPage = new MenuPage(this._username);
                NavigationService.Navigate(menuPage);
            }
        }

        private void TxtMail_OnChanged(object sender, TextChangedEventArgs args)
        {
            BtnSignup.IsEnabled = ((txtMail.Text != "") && (pswdPasswordBox.Password != "") && (Helper.IsValidEmailAddress(txtMail.Text)));
        }

        private void PswdPasswordBox_OnPasswordChanged(object sender, RoutedEventArgs e)
        {
            BtnSignup.IsEnabled = ((txtMail.Text != "") && (pswdPasswordBox.Password != ""));
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
