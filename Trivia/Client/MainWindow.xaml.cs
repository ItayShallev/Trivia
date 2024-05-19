using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Client.Communication;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Socket _conn;

        public MainWindow()
        {
            InitializeComponent();
            InitializeConnection();
        }

        private async void InitializeConnection()
        {
            _conn = new Communication.Socket(Constants.SERVER_IP, Constants.SERVER_PORT);
            _conn.Start();
        }

        private void LoginButton_OnClick(object sender, RoutedEventArgs e)
        {
            string messageContent = JsonSerializer.Serialize(new LoginRequest(UsernameTextBox.Text, PasswordTextBox.Text));
            _conn.SendMessage(Helper.BuildRequest(Constants.LoginRequestId, messageContent));
        }

        private void SignupButton_OnClick(object sender, RoutedEventArgs e)
        {
            string messageContent = JsonSerializer.Serialize(new SignupRequest(UsernameTextBox.Text, PasswordTextBox.Text, MailTextBox.Text));
            _conn.SendMessage(Helper.BuildRequest(Constants.SignupRequestId, messageContent));
        }

        protected override void OnClosed(EventArgs e)
        {
            _conn.CloseConnection();
            base.OnClosed(e);
        }
    }
}