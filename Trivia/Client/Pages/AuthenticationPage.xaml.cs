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

        private void BtnLogin_OnClick(object sender, RoutedEventArgs e)
        {
            string messageContent = JsonSerializer.Serialize(new LoginRequest(UsernameTextBox.Text, PasswordBox.Password));
            Communicator.Connection.SendMessage(Helper.BuildRequest(Constants.LoginRequestId, messageContent));
        }

        private void BtnSignup_OnClick(object sender, RoutedEventArgs e)
        {
            string messageContent = JsonSerializer.Serialize(new SignupRequest(UsernameTextBox.Text, PasswordBox.Password, "Testing@gmail.com"));
            Communicator.Connection.SendMessage(Helper.BuildRequest(Constants.SignupRequestId, messageContent));
        }
    }
}
