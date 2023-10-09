/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/
#ifndef PRINTEMPS_OPTION_VERBOSE_H__
#define PRINTEMPS_OPTION_VERBOSE_H__

namespace printemps::option::verbose {
/*****************************************************************************/
enum Verbose : int {  //
    Off,
    Warning,
    Outer,
    Full,
    Debug
};

/*****************************************************************************/
static std::unordered_map<std::string, Verbose> VerboseMap = {
    {"Off", Verbose::Off},          //
    {"Warning", Verbose::Warning},  //
    {"Outer", Verbose::Outer},      //
    {"Full", Verbose::Full},        //
    {"Debug", Verbose::Debug}       //
};

/*****************************************************************************/
static std::unordered_map<Verbose, std::string> VerboseInverseMap = {
    {Verbose::Off, "Off"},          //
    {Verbose::Warning, "Warning"},  //
    {Verbose::Outer, "Outer"},      //
    {Verbose::Full, "Full"},        //
    {Verbose::Debug, "Debug"}};

}  // namespace printemps::option::verbose

#endif
/*****************************************************************************/
// END
/*****************************************************************************/