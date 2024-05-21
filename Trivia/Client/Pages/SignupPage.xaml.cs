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
        public SignupPage()
        {
            InitializeComponent();

            // For debugging purposes - needs to be removed
            ////////
            string messageContent1 = JsonSerializer.Serialize(new LoginRequest("test", "test"));
            Communicator.Connection.SendMessage(Helper.BuildRequest(Constants.LoginRequestId, messageContent1));
            ResponseInfo responseInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());
            ////////
        }

        private void BtnMenu_OnClick(object sender, RoutedEventArgs e)
        {
            MenuPage menuPage = new MenuPage("USERNAME");
            NavigationService.Navigate(menuPage);
        }
    }
}
