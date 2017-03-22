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

namespace Lab_6_pms
{
   
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        Shape getShape()
        {
            Random rnd = new Random();
            if (rnd.Next(0,100)>=50)
            {
                return new Ellipse();
                
            }
            else return new Rectangle();
        }
        public MainWindow()
        {
            InitializeComponent(); 
            Color myRgbColor = new Color(); 
            Random rnd = new Random();
            myRgbColor = Color.FromRgb(Convert.ToByte(rnd.Next(30, 200)), Convert.ToByte(rnd.Next(30, 200)), Convert.ToByte(rnd.Next(30, 200)));

            //Polygon myPoly = new Polygon();
            //myPoly.Points.Add(new Point(10, 10));
            //myPoly.Points.Add(new Point(450, 350));
            //myPoly.Points.Add(new Point(450, 200));
            //myPoly.Fill = new SolidColorBrush(myRgbColor);
            //LayoutRoot.Children.Add(myPoly);
            //myPoly.MouseDown += new MouseButtonEventHandler(myPoly_MouseDown);
            //LayoutRoot.MouseMove += new MouseEventHandler(canvas1_MouseMove);
            //LayoutRoot.MouseUp += new MouseButtonEventHandler(canvas1_MouseUp);
        
            int count = rnd.Next(3,7);
            List<Shape> shapes = new List<Shape>();
            for (int i = 0; i < count; i++)
            {
                if(i==count-1)
                    shapes.Add(new Rectangle());
                else
                shapes.Add(getShape());
                shapes[i].Height = rnd.Next(30, 200);
                shapes[i].Width = rnd.Next(30, 200);
                shapes[i].Fill = new SolidColorBrush(myRgbColor);
                shapes[i].Fill.Opacity = 0.5;
                shapes[i].Stroke = new SolidColorBrush(myRgbColor);
                myRgbColor = Color.FromRgb(Convert.ToByte(rnd.Next(0, 255)), Convert.ToByte(rnd.Next(0, 255)), Convert.ToByte(rnd.Next(0, 255)));
                shapes[i].StrokeThickness = 7;
                Canvas.SetLeft(shapes[i], rnd.Next(0, 500));
                Canvas.SetTop(shapes[i], rnd.Next(0, 300));
                LayoutRoot.Children.Add(shapes[i]);
                shapes[i].MouseLeftButtonDown += new MouseButtonEventHandler(shape_MouseLeftButtonDown);
                shapes[i].MouseMove+=new MouseEventHandler(shape_MouseMove);
                shapes[i].MouseLeftButtonUp+=new MouseButtonEventHandler(shape_MouseLeftButtonUp);
                Canvas.SetRight(shapes[i], shapes[i].Width + Canvas.GetLeft(shapes[i]));
                Canvas.SetBottom(shapes[i], shapes[i].Height + Canvas.GetTop(shapes[i]));
            }
            
        }
        bool dragging;
        Point clickV;
        Shape selectedShape;
        void canvas1_MouseUp(object sender, MouseButtonEventArgs e)
        {
            dragging = false;
        }

        void canvas1_MouseMove(object sender, MouseEventArgs e)
        {
            Polygon p = selectedShape as Polygon;
            
            if (dragging)
            {
                
                    Canvas.SetLeft(p, e.GetPosition(LayoutRoot).X - clickV.X);
                    Canvas.SetTop(p, e.GetPosition(LayoutRoot).Y - clickV.Y);
                
            }
        }

        void myPoly_MouseDown(object sender, MouseButtonEventArgs e)
        {
            dragging = true;
            selectedShape = sender as Shape;
            clickV = e.GetPosition(selectedShape);
        }

        
      






        bool captured = false;
        double x_shape, x_canvas, y_shape, y_canvas, x1_shape,y1_shape;
        UIElement source = null;

        private void shape_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            source = (UIElement)sender;
            Mouse.Capture(source);
            
            captured = true;
            x_shape = Canvas.GetLeft(source);
            x1_shape = Canvas.GetRight(source);
            x_canvas = e.GetPosition(LayoutRoot).X;
            y_shape = Canvas.GetTop(source);
            y1_shape = Canvas.GetBottom(source);
            y_canvas = e.GetPosition(LayoutRoot).Y;
        }

        private void shape_MouseMove(object sender, MouseEventArgs e)
        {
            if (captured)
            {
                double x = e.GetPosition(LayoutRoot).X;
                double y = e.GetPosition(LayoutRoot).Y;
                x_shape += x - x_canvas;
                x1_shape += x - x_canvas;
                if (x_shape >= 0 && x1_shape<= 725)
                {
                    Canvas.SetLeft(source, x_shape);
                    Canvas.SetRight(source, x1_shape);
                }
                x_canvas = x;
                y_shape += y - y_canvas;
                y1_shape += y - y_canvas;
                if (y_shape >= 30 && y1_shape <= 550)
                {
                    Canvas.SetTop(source, y_shape);
                    Canvas.SetBottom(source, y_shape);
                }
                y_canvas = y;
            }
        }

        private void shape_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Mouse.Capture(null);
            captured = false;
        }


        private void btnExit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Label_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }

    }
}
