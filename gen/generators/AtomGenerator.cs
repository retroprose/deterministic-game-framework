using System.Diagnostics.CodeAnalysis;
using System.Diagnostics.Tracing;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace gen;


public class AtomGenerator
{
    public static AtomGenerator Create(string enumPath, string outPath)
    {
        return new AtomGenerator {
            OutPath = outPath,
            EnumPath = enumPath
        };
    }

    public AtomGenerator() {
        OutPath = "";
        EnumPath = "";
    }

    public string OutPath;
    public string EnumPath;


    public void Generate()
    {
        var lines = File.ReadAllLines(EnumPath);
        var sw = new StringWriter();

        var sep = "";
        var space = "";
        var name = "";
        foreach (var line in lines)
        {
            var split = line.Split(null);
            if (line.Contains("struct"))
            {
                space = GetNonEmpty(split, 2);
            }
            else if (line.Contains("="))
            {
                name = GetNonEmpty(split, 1);
                // spaces are important for tabbing!
                sw.Write($"{sep}            {{\"{space}::{name}\", {space}::{name}}}");
                sep = ",\n";
            }
            else
            {
                // do nothing
            }
        }

        #region UglyTextAtoms
        File.WriteAllText($"{OutPath}atoms.hpp", @$"#ifndef GENERATED_ATOMS_HPP
#define GENERATED_ATOMS_HPP

#include <string>
#include <map>

#include <enums.hpp>

struct Atoms {{
    template<typename T>
    inline static T get(std::string s) {{
        static std::map<std::string, uint32_t> m = {{
{sw.ToString()}
        }};
        return static_cast<T>(m[s]);
    }}
}};

#endif // GENERATED_ATOMS_HPP");
        #endregion
    
    }

    public string? GetNonEmpty(string[]? list, int number)
    {
        if (list == null)
        {
            return null;
        } 
        string? ret = null;
        int index = 0;
        int count = 0;
        while (ret == null && index < list.Length)
        {
            if (!string.IsNullOrEmpty(list[index].Trim()))
            {
                count++;
                if (count == number)
                {
                    ret = list[index];
                }
            }
            index++;
        }
        return ret;
    }

}
