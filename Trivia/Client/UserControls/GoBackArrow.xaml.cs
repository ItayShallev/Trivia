using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
using Client.Pages;

namespace Client.UserControls
{
    /// <summary>
    /// Interaction logic for GoBackArrow.xaml
    /// </summary>
    public partial class GoBackArrow : UserControl
    {
        public event RoutedEventHandler GoBackClicked;      // Custom event

        public GoBackArrow()
        {
            InitializeComponent();
            BtnGoBackArrow.Click += BtnGoBackArrow_Click;       // Adding the event invoker function to the BtnGoBackArrow OnClick list
        }

        private void BtnGoBackArrow_Click(object sender, RoutedEventArgs e)
        {
            GoBackClicked?.Invoke(this, e);         // Invoking a "GoBackClicked" event
        }
    }
}
