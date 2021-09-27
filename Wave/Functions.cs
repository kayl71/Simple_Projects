using System;
using System.Collections.Generic;

namespace Wave.Classes
{
    public class Functions
    {
        public readonly double delta;

        public Functions(double delta) {
            this.delta = delta;
        }

        public List<Point> Sinusoid(double startPosX, int countDelta) {
            List<Point> points = new List<Point>();

            double thisX = startPosX;

            for (int i = 0; i < countDelta; i++) {
                points.Add(new Point(thisX, Math.Sin(thisX)));
                thisX += delta;
            }

            return points;
        }

    }

    public struct Point {
        public double x, y;
        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    };
}
