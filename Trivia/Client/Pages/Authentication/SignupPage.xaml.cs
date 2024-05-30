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

        }


        private void BtnSignup_OnClick(object sender, RoutedEventArgs e)
        {
            // get the user input
            string password = pswdPasswordBox.Password;
            string email = txtMail.Text;

            // build and send the request
            string messageContent = JsonSerializer.Serialize(new SignupRequest(this._username, password, email));
            string message = Helper.BuildRequest(Client.Constants.SignupRequestId, messageContent);
            Communicator.Connection.SendMessage(message);


            ///////// TODO: DEBUG TO CHECK DESERIALIZER
            // receive the response
            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());
            //SignupResponse signupResp = JsonSerializer.Deserialize<SignupResponse>(respInfo.Message);

            if (respInfo.ResponseId == Client.Constants.SignupResponseId)
            {
                MenuPage menuPage = new MenuPage(this._username);
                NavigationService.Navigate(menuPage);
            }
        }
    }
}
