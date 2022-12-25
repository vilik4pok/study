using System;
using System.Runtime.InteropServices;

namespace ConsoleApplication1
{
    class Program
    {
        [DllImport("SquareNegative.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void SquareNegative(IntPtr arr, int size);
        public static extern void SquareNegative(double[] arr, int size);
        [DllImport("SquareNegative.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReadArray(double[] arr, int size);
        [DllImport("SquareNegative.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PrintArray(double[] arr, int size);

        static void Main(string[] args)
        {
            int count = 0;
            bool flag = false;
            while(!flag)
            {
                Console.Write("Введите кол-во элементов массива (>=0): ");
                flag = int.TryParse(Console.ReadLine(), out count);
                if (count < 0)
                    flag = false;
            }
            double[] arr = new double[count];
            ReadArray(arr, count);
            SquareNegative(arr, count);

            Console.WriteLine("Результирующий массив: ");
            PrintArray(arr, count);
        }
    }
}
