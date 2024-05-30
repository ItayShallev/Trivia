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
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        private string _username;
        public LoginPage(string username)
        {
            this._username = username;
            InitializeComponent();

            
        }
        

        private void BtnLogin_OnClick(object sender, RoutedEventArgs e)
        {
            // get the password
            string password = pswdPasswordBox.Password;

            // build and send the request
            string messageContent = JsonSerializer.Serialize(new LoginRequest(this._username, password));
            string message = Helper.BuildRequest(Client.Constants.LoginRequestId, messageContent);
            Communicator.Connection.SendMessage(message);


            ///////// TODO: DEBUG TO CHECK DESERIALIZER
            // receive the response
            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());

            /// if the response is ok
            if (respInfo.ResponseId == Client.Constants.LoginResponseId)
            {
                // navigate to the menu page
                MenuPage menuPage = new MenuPage(this._username);
                NavigationService.Navigate(menuPage);
            }
        }
    }
}
