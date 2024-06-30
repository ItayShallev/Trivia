using Client.Communication;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using Client.UserControls;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        private string _username;

        public LoginPage(string username)
        {
            this._username = username;
            InitializeComponent();

            // Focusing on the password box
            pswdPasswordBox.Focus();
        }

        private void PswdPasswordBox_OnPasswordChanged(object sender, RoutedEventArgs e)
        {
            BtnLogin.IsEnabled = (pswdPasswordBox.Password != "");
        }

        private void BtnLogin_OnClick(object sender, RoutedEventArgs e)
        {
            // Input validation
            if (pswdPasswordBox.Password == "")
            {
                BtnLogin.IsEnabled = false;
            }

            // Sending a login request to the server
            Helper.SendRequest(Constants.LoginRequestId, JsonSerializer.Serialize(new LoginRequest(this._username, pswdPasswordBox.Password)));

            // receive the response
            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());

            // if the response is ok
            if (respInfo.ResponseId == Client.Constants.LoginResponseId)
            {
                // navigate to the menu page
                MenuPage menuPage = new MenuPage(this._username);
                NavigationService.Navigate(menuPage);
            }
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
