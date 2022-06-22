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
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MainApp
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        const int LINETHICKNESS = 5;

        bool _isMoving;
        bool _isSelecting = false;
        Point _startMovePosition;
        Path _currentBoxSelectedBorder = null;//框选矩形框

        Point _CPoint = new Point(740, 375);
        CPRect _rect;
        CPCube _cube;
        List<CPLine> _shapes;
        public MainWindow()
        {
            _shapes = new List<CPLine>();
            Loaded += MainWindow_Loaded;
            InitializeComponent();
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            CPLine line1 = new CPLine(0, 0, 1480, 750);
            CPLine line2 = new CPLine(1480, 0, 0, 750);
            CreateAxis();
            CreateCube();
        }

        private void CreateAxis()
        {
            Point xax = new Point(10000, 0);
            Point yax = new Point(-3536, -3536);
            Point zax = new Point(0, -10000);
            SolidColorBrush brush = new SolidColorBrush();
            brush.Color = Colors.Red;
            Line xAxis = new Line() { StrokeThickness = 1, X1 = 0 + 740, Y1 = 0 + 375, X2 = xax.X + 740, Y2 = xax.Y + 375, Stroke = brush };
            Line yAxis = new Line() { StrokeThickness = 1, X1 = 0 + 740, Y1 = 0 + 375, X2 = yax.X + 740, Y2 = yax.Y + 375, Stroke = brush };
            Line zAxis = new Line() { StrokeThickness = 1, X1 = 0 + 740, Y1 = 0 + 375, X2 = zax.X + 740, Y2 = zax.Y + 375, Stroke = brush };
            _canvas.Children.Add(xAxis);
            _canvas.Children.Add(yAxis);
            _canvas.Children.Add(zAxis);
        }
        private void CreateRect()
        {
            CPRect rect = new CPRect(new Point(740, 375), 200, 200);
            _shapes = rect.OutLines;
            _rect = rect;
            DrawLines(rect.OutLines);
        }

        private void CreateCube()
        {
            CPCube cube = new CPCube(new Point(0, 0), 300, -200, 100);
            _cube = cube;
            DrawLines(cube.OutLines);
        }
        private void DrawLines(List<CPLine> lines)
        {
            foreach (var item in _shapes)
            {
                _canvas.Children.Remove(item.Shape);
            }

            _shapes = new List<CPLine>();
            foreach (var line in lines)
            {
                SolidColorBrush brush = new SolidColorBrush();
                brush.Color = Colors.Black;
                line.Shape.Stroke = brush;
                _shapes.Add(line);
                _canvas.Children.Add(line.Shape);
            }
        }
        #region 鼠标滚轮控制界面放大缩小、框选事件
        private void border_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Right)
            {
                _canvas.Cursor = Cursors.Arrow;
                _isSelecting = false;
            }

            if (e.MiddleButton == MouseButtonState.Pressed
                && e.LeftButton == MouseButtonState.Released
                && e.RightButton == MouseButtonState.Released)
            {
                _startMovePosition = e.GetPosition(_borderMain);
            }
            else if (e.MiddleButton == MouseButtonState.Released &&
                e.LeftButton == MouseButtonState.Pressed && e.RightButton == MouseButtonState.Released && _isSelecting)
            {
                _startMovePosition = e.GetPosition(_canvas);
            }

            _isMoving = true; //鼠标框选事件不启动
                              //e.Handled = true;
        }

        private void border_PreviewMouseUp(object sender, MouseButtonEventArgs e)
        {
            if (_isMoving)
            {
                _isMoving = false;
            }
            if (_currentBoxSelectedBorder != null)
            {
                //获取选框的矩形位置
                Point tempEndPoint = e.GetPosition(_canvas);
                Rect tempRect = new Rect(_startMovePosition, tempEndPoint);
                //获取子控件
                List<Path> childList = GetChildObjects<Path>(_canvas);
                List<Guid> selctSlabs = new List<Guid>();

                foreach (var child in childList)
                {
                    var obj = child.Tag;
                    if (obj == null)
                    {
                        continue;
                    }

                    var pts = GetPathPoints(child);
                    if (pts.Count > 1)
                    {
                        var minX = Math.Min(Math.Min(pts[0].X, pts[1].X), Math.Min(pts[2].X, pts[3].X));
                        var minY = Math.Min(Math.Min(pts[0].Y, pts[1].Y), Math.Min(pts[2].Y, pts[3].Y));
                        var maxX = Math.Max(Math.Max(pts[0].X, pts[1].X), Math.Max(pts[2].X, pts[3].X));
                        var maxY = Math.Max(Math.Max(pts[0].Y, pts[1].Y), Math.Max(pts[2].Y, pts[3].Y));
                        Rect childRect = new Rect(new Point(minX, minY), new Point(maxX, maxY));
                        if (_startMovePosition.X < tempEndPoint.X)//正选
                        {
                            if (tempRect.Contains(childRect))
                            {
                                selctSlabs.Add(new Guid(obj.ToString()));
                            }

                        }
                        else  //反选
                        {
                            if (tempRect.IntersectsWith(childRect))
                            {
                                selctSlabs.Add(new Guid(obj.ToString()));
                            }
                        }
                    }
                }
                //_canvas.Children.Remove(_currentBoxSelectedBorder);
                _canvas.Children.RemoveAt(_canvas.Children.Count - 1);
                _currentBoxSelectedBorder = null;
            }
            //e.Handled = true;
        }
        /// <summary>
        /// 获取Path对象的点集
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        private List<Point> GetPathPoints(Path path)
        {
            var pts = new List<Point>();
            PathGeometry pathGeometry = path.Data as PathGeometry;
            if (pathGeometry == null)
            {
                return pts;
            }

            PathFigureCollection pathFigures = pathGeometry.Figures;
            foreach (var item in pathFigures)
            {
                pts.Add(item.StartPoint);
                PathSegmentCollection pathSegmentCollection = item.Segments;
                foreach (var tempItem in pathSegmentCollection)
                {
                    if (tempItem is LineSegment)
                    {
                        LineSegment lineSegment = tempItem as LineSegment;
                        pts.Add(lineSegment.Point);
                    }
                    else if (tempItem is ArcSegment)
                    {
                        ArcSegment arcSegment = tempItem as ArcSegment;
                        pts.Add(arcSegment.Point);
                    }
                }
            }
            return pts;
        }

        /// <summary>
        /// 获取子对象
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="obj"></param>
        /// <returns></returns>
        private List<T> GetChildObjects<T>(DependencyObject obj) where T : FrameworkElement
        {
            DependencyObject child = null;
            List<T> childList = new List<T>();
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(obj); i++)
            {
                child = VisualTreeHelper.GetChild(obj, i);
                if (child is T)
                {
                    childList.Add((T)child);
                }
                childList.AddRange(GetChildObjects<T>(child));
            }
            return childList;
        }
        private void border_MouseMove(object sender, MouseEventArgs e)
        {
            // startMovePosition=RVBorder.RvMouseMove(sender, e, _canvas, startMovePosition, _borderMain, isMoving);
            if (e.MiddleButton == MouseButtonState.Pressed && e.LeftButton == MouseButtonState.Released
                 && e.RightButton == MouseButtonState.Released)
            {
                if (_isMoving)
                {
                    Point currentPoint = e.GetPosition(_borderMain);  //不能用 inside，必须用outside
                    Vector v = currentPoint - _startMovePosition;
                    TransformGroup tg = _canvas.RenderTransform as TransformGroup;
                    if (tg == null)
                    {
                        tg = new TransformGroup();
                    }

                    tg.Children.Add(new TranslateTransform(v.X, v.Y));//centerX和centerY用外部包装元素的坐标，不能用内部被变换的Canvas元素的坐标
                    _canvas.RenderTransform = tg;
                    _startMovePosition = currentPoint;

                }
            }
            else if (e.MiddleButton == MouseButtonState.Released && e.LeftButton == MouseButtonState.Pressed
                 && e.RightButton == MouseButtonState.Released && _isSelecting)
            {
                if (_isMoving)
                {
                    Point tempEndPoint = e.GetPosition(_canvas);
                    DrawMultiselectBorder(tempEndPoint, _startMovePosition);
                }
            }
            e.Handled = true;
        }

        private void DrawMultiselectBorder(Point endPoint, Point startPoint)
        {
            if (_currentBoxSelectedBorder != null)
            {
                _canvas.Children.Remove(_currentBoxSelectedBorder);
            }

            var pt1 = new Point(startPoint.X, startPoint.Y);
            var pt2 = new Point(endPoint.X, startPoint.Y);
            var pt3 = new Point(endPoint.X, endPoint.Y);
            var pt4 = new Point(startPoint.X, endPoint.Y);
            _currentBoxSelectedBorder = CreatePathByPoints(new List<Point>() { pt1, pt2, pt3, pt4 }, Brushes.Black, LINETHICKNESS);
            _currentBoxSelectedBorder.Fill = new SolidColorBrush(Colors.AliceBlue);
            _currentBoxSelectedBorder.Fill.Opacity = 0.8;
            _currentBoxSelectedBorder.StrokeThickness = 20;
            _currentBoxSelectedBorder.Stroke = new SolidColorBrush(Colors.Gray);
            Canvas.SetZIndex(_currentBoxSelectedBorder, 1000);
            //_currentBoxSelectedBorder.Width = Math.Abs(endPoint.X - startPoint.X);
            //_currentBoxSelectedBorder.Height = Math.Abs(endPoint.Y - startPoint.Y);

            if (endPoint.X - startPoint.X >= 0)
            {
                //Canvas.SetLeft(_currentBoxSelectedBorder, startPoint.X);
            }
            else
            {
                _currentBoxSelectedBorder.StrokeDashArray = new DoubleCollection() { 10, 10 };
            }
            _currentBoxSelectedBorder.MouseUp += border_PreviewMouseUp;
            _canvas.Children.Add(_currentBoxSelectedBorder);
        }

        /// <summary>
        /// 根据点集创建路径
        /// </summary>
        /// <param name="points"></param>
        /// <param name="brush"></param>
        /// <param name="strokeThickness"></param>
        /// <param name="isClosed"></param>
        /// <returns></returns>
        private Path CreatePathByPoints(List<Point> points, Brush brush, double strokeThickness = 1, bool isClosed = true)
        {
            PathGeometry pathGeometry = new PathGeometry();
            PathFigure pathFigure = new PathFigure();
            pathFigure.StartPoint = points[0];

            PathSegmentCollection pathSegmentCollection = new PathSegmentCollection();
            for (int i = 1; i < points.Count; i++)
            {
                LineSegment lineSegment = new LineSegment();
                lineSegment.Point = points[i];
                pathSegmentCollection.Add(lineSegment);
            }

            pathFigure.Segments = pathSegmentCollection;
            pathFigure.IsClosed = isClosed;

            PathFigureCollection pathFigures = new PathFigureCollection();
            pathFigures.Add(pathFigure);
            pathGeometry.Figures = pathFigures;

            Path path = new Path();
            path.Stroke = brush;
            path.StrokeThickness = strokeThickness;
            path.Data = pathGeometry;

            return path;
        }
        private void border_PreviewMouseWheel(object sender, MouseWheelEventArgs e)
        {
            //RVBorder.RvPreviewMouseWheel(sender, e, _canvas, _borderMain);
            Point currentPoint = e.GetPosition(_borderMain);  //不能用 inside，必须用outside

            TransformGroup tg = _canvas.RenderTransform as TransformGroup;
            if (tg == null)
            {
                tg = new TransformGroup();
            }

            double scale;
            if (e.Delta > 0)
            {
                scale = 1.08;
                //_canvasScale = _canvasScale * 1.6;
            }
            else
            {
                scale = 0.92;
                //_canvasScale = _canvasScale / 1.6;
            }

            //centerX和centerY用外部包装元素的坐标，不能用内部被变换的Canvas元素的坐标
            tg.Children.Add(new ScaleTransform(scale, scale, currentPoint.X, currentPoint.Y));
            _canvas.RenderTransform = tg;
            e.Handled = true;
        }

        #endregion

        private void _canvas_MouseMove(object sender, MouseEventArgs e)
        {
            Point pt = e.GetPosition(_canvas);
            _posText.Text = "X:" + Math.Round(pt.X, 2) + "  Y:" + Math.Round(pt.Y, 2);
        }


        private void Rotate_Click(object sender, RoutedEventArgs e)
        {
            switch (_rotAxis.Text)
            {
                case "X":
                    _cube.RotateX(Math.PI / 10);
                    break;
                case "Y":
                    _cube.RotateZ(Math.PI / 10);
                    break;
                case "Z":
                    _cube.RotateY(Math.PI / 10);
                    break;
                default:
                    _cube.RotateX(Math.PI / 10);
                    break;
            }
            DrawLines(_cube.OutLines);
        }

        private void TransUP_Click(object sender, RoutedEventArgs e)
        {

            switch (_rotAxis.Text)
            {
                case "X":
                    _cube.Translate(20, 0, 0);
                    break;
                case "Y":
                    _cube.Translate(0, 0, 20);
                    break;
                case "Z":
                    _cube.Translate(0, -20, 0);
                    break;
                default:
                    _cube.Translate(20, 0, 0);
                    break;
            }
            DrawLines(_cube.OutLines);
        }

        private void TransDown_Click(object sender, RoutedEventArgs e)
        {
            switch (_rotAxis.Text)
            {
                case "X":
                    _cube.Translate(-20, 0, 0);
                    break;
                case "Y":
                    _cube.Translate(0, 0, -20);
                    break;
                case "Z":
                    _cube.Translate(0, 20, 0);
                    break;
                default:
                    _cube.Translate(-20, 0, 0);
                    break;
            }
            DrawLines(_cube.OutLines);
        }


        private void NeRotate_Click(object sender, RoutedEventArgs e)
        {

            switch (_rotAxis.Text)
            {
                case "X":
                    _cube.RotateX(-Math.PI / 10);
                    break;
                case "Y":
                    _cube.RotateZ(-Math.PI / 10);
                    break;
                case "Z":
                    _cube.RotateY(-Math.PI / 10);
                    break;
                default:
                    _cube.RotateX(-Math.PI / 10);
                    break;
            }
            DrawLines(_cube.OutLines);
        }
    }
}
