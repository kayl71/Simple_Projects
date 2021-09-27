using System;
using System.Threading;
using System.Collections.Generic;
using System.Text;

namespace Wave
{

    public class Program
    {

        protected static readonly int BUFFER = 5;
        public static Queue<string> bitmap;
        public static bool running;
        public static Classes.Functions functions;
        protected double thisX;

        public static List<string> points;

        static void Main(string[] args)
        {
            
            running = true;
            functions = new Classes.Functions(0.11);
            points = Classes.FunctionReader.GetListPoints(functions.Sinusoid(0, 58), functions.delta);
            bitmap = new Queue<string>();

            Thread thread = new Thread(new ThreadStart(BitMapThread.F));
            thread.Start();

            StringBuilder sb = new StringBuilder();
            sb.Append('\n', 20);

            while (running) {
                if (bitmap.Count > 0)
                {
                    //Console.WriteLine(sb.ToString());
                    Console.SetCursorPosition(0, 0);
                    Console.Write(bitmap.Dequeue());
                }
                Thread.Sleep(25);
            }

            thread.Join();

        }

        public class BitMapThread {

            private static int cur = 0;
            private static int size = 61;
            public static void F() {
                while (running) {
                    if (bitmap.Count >= BUFFER)
                        Thread.Sleep(10);
                    else {
                        StringBuilder sb = new StringBuilder();
                        for (int i = 0; i < size; i++) 
                            sb.Append(points[(cur + i) % 58]);

                        bitmap.Enqueue(sb.ToString());
                        cur++;
                    }
                }
            }
        }

    }
}
