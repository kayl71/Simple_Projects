using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wave.Classes
{
    class FunctionReader
    {

        private StringBuilder sb;
        private static readonly int MAX_SQUARE_COUNT = 25; //In Y 
        private static readonly char SYMBOL = '#';
       

        public FunctionReader(List<Point> points, double square_size) {
            sb = new StringBuilder();

            Point minPoint =  points[0];

            for (int i = 1; i < points.Count; i++) {
                if (minPoint.y > points[i].y)
                    minPoint = points[i];
            }

            for (int i = 0; i < points.Count; i++) {
                int square_count = (int)(Math.Round(Math.Abs(points[i].y - minPoint.y)/square_size));
                square_count = Math.Min(square_count, MAX_SQUARE_COUNT);
                sb.Append(SYMBOL, square_count)
                  .Append(' ', MAX_SQUARE_COUNT - square_count)
                  //.Append(points[i].y)
                  .Append('\n');
            }
        }

        public static List<string> GetListPoints(List<Point> points, double square_size) {
            StringBuilder sb = new StringBuilder();
            List<string> list = new List<string>();

            Point minPoint = points[0];

            for (int i = 1; i < points.Count; i++)
            {
                if (minPoint.y > points[i].y)
                    minPoint = points[i];
            }

            for (int i = 0; i < points.Count; i++)
            {
                int square_count = (int)(Math.Round(Math.Abs(points[i].y - minPoint.y) / square_size));
                square_count = Math.Min(square_count, MAX_SQUARE_COUNT);
                sb.Append(SYMBOL, square_count)
                  .Append(' ', MAX_SQUARE_COUNT - square_count)
                  .Append('\n');
                list.Add(sb.ToString());
                sb.Clear();
            }

            return list;
        }

        public override string ToString()
        {
            return sb.ToString();
        }
    }
}
