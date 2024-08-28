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
using MaterialDesignThemes.Wpf;

namespace Client.UserControls
{
    /// <summary>
    /// Interaction logic for GoBackArrow.xaml
    /// </summary>
    public partial class GoBackArrow : UserControl
    {
        public PackIconKind IconKind
        {
            get { return (PackIconKind)GetValue(IconKindProperty); }
            set { SetValue(IconKindProperty, value); }
        }

        public Brush IconColor
        {
            get { return (Brush)GetValue(IconColorProperty); }
            set { SetValue(IconColorProperty, value); }
        }

        public Brush ButtonBackground
        {
            get { return (Brush)GetValue(ButtonBackgroundProperty); }
            set { SetValue(ButtonBackgroundProperty, value); }
        }

        public static readonly DependencyProperty IconKindProperty =
            DependencyProperty.Register("IconKind", typeof(PackIconKind), typeof(GoBackArrow), new PropertyMetadata(PackIconKind.ArrowLeftBox));

        public static readonly DependencyProperty IconColorProperty =
            DependencyProperty.Register("IconColor", typeof(Brush), typeof(GoBackArrow), new PropertyMetadata(Brushes.White));

        public static readonly DependencyProperty ButtonBackgroundProperty =
            DependencyProperty.Register("ButtonBackground", typeof(Brush), typeof(GoBackArrow), new PropertyMetadata(Brushes.DodgerBlue));

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
