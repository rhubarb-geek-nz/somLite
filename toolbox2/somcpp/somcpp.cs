/**************************************************************************
 *
 *  Copyright 2026, Roger Brown
 *
 *  This file is part of Roger Brown's Toolkit.
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */
 
using System;
using RhubarbGeekNz.CPreProcessor;

namespace somcpp
{
    class Program
    {
        static void Main(string[] args)
        
        {
            var builder = Processor
                .CreateBuilder()
                .UseOutputWriter(new StringPipeline(
                    s => Console.Out.WriteLine(s)
                ))
                .UseWarningHandler((c, s) =>
                {
                    Console.Error.WriteLine(s);
                    return false;
                })
                .UseErrorHandler((c, s) =>
                {
                    throw new CPreProcessorException(c, s);
                })
                .UseIncludeDirectory(Environment.CurrentDirectory);

            bool lineNumbers = true;

            foreach (var arg in args)
            {
                if (arg[0] != '-')
                {
                    throw new ArgumentException($"Unrecognized argument {arg}");
                }

                switch (arg[1])
                {
                    case 'D':
                        {
                            int i = arg.IndexOf('=');

                            if (i < 0)
                            {
                                builder = builder.UseMacroDefinition(arg.Substring(2), "1");
                            }
                            else
                            {
                                builder = builder.UseMacroDefinition(arg.Substring(2, i - 2), arg.Substring(i + 1));
                            }
                        }
                        break;

                    case 'I':
                        builder = builder.UseIncludePath(arg.Substring(2));
                        break;

                    default:
                        switch (arg)
                        {
                            case "-trigraphs":
                                builder = builder.UseTriGraphs(true);
                                break;

                            case "-P":
                                lineNumbers = false;
                                break;

                            default:
                                throw new ArgumentException($"Unrecognized argument {arg}");
                        }
                        break;
                }
            }

            builder.UseIncludePath(".");

            using (var cpp = builder.UseLineNumbers(lineNumbers).Build())
            {
                string input;

                while ((input = Console.ReadLine()) != null)
                {
                    cpp.Write(input);
                }
            }
        }
    }
}
