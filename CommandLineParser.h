#pragma once

#include <vector>
#include <string>

/****
 * Adopted from: http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
 */
class CommandLineParser
{
   public:

      CommandLineParser( int &argc, char **argv );

      const std::string getCmdOption(const std::string &option) const;
        
      bool cmdOptionExists(const std::string &option) const;
    
   private:
   
      std::vector< std::string > tokens;
};

