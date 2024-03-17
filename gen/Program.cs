using System.Diagnostics.CodeAnalysis;
using System.Diagnostics.Tracing;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace gen;


class Program
{
    static void Main(string[] args)
    {
        GenerateHppFiles();
    }

    static void GenerateHppFiles()
    {
        string OutPath = "../include/generated/";

        Console.WriteLine("Generation Started...");
     
        AtomGenerator.Create("../include/enums.hpp", OutPath).Generate();
        Console.WriteLine("Atoms Generated.");

        JsonGenerator.Create("../assets/json/", OutPath).Generate();
        Console.WriteLine("Jsons Generated.");

        //PrefabGenerator.Create("../assets/json/prefabs.json", OutPath).Generate();
        //Console.WriteLine("Prefabs Generated.");

        Console.WriteLine("Generation Complete.");
    }
}