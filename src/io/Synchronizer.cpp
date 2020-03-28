#include "Synchronizer.h"
#include <fstream>
#include <QString>
#include <QStringList>

inline bool contains(std::string original, std::string comparison)
{
    return original.find(comparison) != std::string::npos;
}

void raydelto::Synchronizer::Process(std::string sourcePath, std::string destinationPath, raydelto::Time variation)
{
    std::string line;
    std::ifstream reader(sourcePath);
    std::ofstream writer(destinationPath);
    while(!reader.eof())
    {
        getline(reader,line);
        if(contains(line,":") && contains(line,",") && contains(line,"-") && contains(line,">"))
        {
            QString qline = QString::fromStdString(line);
            QStringList qtimes = qline.split(" --> ");
            raydelto::Time startTime = raydelto::Time(qtimes.at(0));
            raydelto::Time endTime = raydelto::Time(qtimes.at(1));
            startTime.Change(variation);
            endTime.Change(variation);
            writer << startTime.ToStdString() << " --> " << endTime.ToStdString() << std::endl;
        }else
        {
            writer << line << std::endl;
        }  
    }
    reader.close();
    writer.close();
}
