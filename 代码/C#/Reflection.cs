using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace ReflectionTest
{
    class Contact
    {
        public string Name { get; private set; }
        public string Address { get; set; }

        public string m_sMail;
        private string m_sPhone;
        public Contact()
        {
        }

        public Contact(string name, string addr)
        {
            Name = name;
            Address = addr;
        }

        public void Print()
        {
            Console.WriteLine("Name: " + Name + "\nAddress: " + Address);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Contact pt = new Contact();
            Type t = pt.GetType();

            ConstructorInfo[] contInfo = t.GetConstructors();
            Console.WriteLine("1.Find the constructor in class:");
            Console.WriteLine("Number of constructors:" + contInfo.Length);
            int num = 0;
            foreach(ConstructorInfo c in contInfo)
            {
                ParameterInfo[] ps = c.GetParameters();
                Console.WriteLine("This is " + num++ + " constructor：");
                foreach (ParameterInfo pi in ps)
                {
                    Console.Write(pi.ParameterType.ToString()+" "+pi.Name + ", ");
                }
                Console.WriteLine();
            }

            FieldInfo[] fldInfo = t.GetFields();
            Console.WriteLine();
            Console.WriteLine("2.FieldInfo in class:");
            foreach (FieldInfo c in fldInfo)
            {
                 Console.WriteLine(c.ToString());
            }

            MemberInfo[] membinfo = t.GetMembers();
            Console.WriteLine();
            Console.WriteLine("3.MemberInfo in class:");
            foreach (MemberInfo c in membinfo)
            {
                Console.WriteLine(c.ToString());
            }

            MethodInfo[] methinfo = t.GetMethods();
            Console.WriteLine();
            Console.WriteLine("4.MethodInfo in class:");
            foreach (MethodInfo c in methinfo)
            {
                Console.WriteLine(c.ToString());
            }

            PropertyInfo[] propinfo = t.GetProperties();
            Console.WriteLine();
            Console.WriteLine("5.PropertyInfo in class:");
            foreach (PropertyInfo c in propinfo)
            {
                Console.WriteLine(c.ToString());
            }

            Console.WriteLine("\n6. Using constructor create instance dynamic:");
            Type[] tt = new Type[2];
            tt[0] = typeof(string);
            tt[1] = typeof(string);

            ConstructorInfo ctInfo = t.GetConstructor(tt);
            object[] obj = new object[2] { "Simon Li", "Shanghai Pudong" };
            object o = ctInfo.Invoke(obj);
            ((Contact)o).Print();

            Console.WriteLine("\n7.Create instance with Activator:");
            Object[] objs = new object[2] { "Alpha Li", "ShenZheng" };
            object ob = Activator.CreateInstance(t, objs);
            ((Contact)ob).Print();

            Console.WriteLine("\n8:Using reflection get object, call properties, methods and fields:");
            object obNew = Activator.CreateInstance(t);
            FieldInfo fi7 = t.GetField("m_sMail");
            fi7.SetValue(obNew, "lipp09");
            PropertyInfo pi7 = t.GetProperty("Name");
            pi7.SetValue(obNew, "Simon Li");
            PropertyInfo pAddr7 = t.GetProperty("Address");
            pAddr7.SetValue(obNew, "Shanghai",null);
            MethodInfo mi7 = t.GetMethod("Print");
            mi7.Invoke(obNew, null);

            Console.WriteLine("\nI. Using reflection with assembly:");
            Assembly ass = Assembly.Load("ReflectionTest");
            Type tRef = ass.GetType("ReflectionTest.Contact");
            object oRef = Activator.CreateInstance(tRef, "Simon Li", "ShenZheng");
            MethodInfo mi = tRef.GetMethod("Print");
            mi.Invoke(oRef, null);

            Console.WriteLine("\nII.Get all types with full name of dll:");
            Assembly assembly = Assembly.Load("mscorlib.dll");
            Type[] aa = assembly.GetTypes();
            foreach(Type a in aa)
            {
                if(a.FullName == "System.String")
                {
                    Console.WriteLine(assembly.GetName());
                    Console.WriteLine("Get System.String type with reflection");
                }
            }
            Console.Read();
        }
    }
}
