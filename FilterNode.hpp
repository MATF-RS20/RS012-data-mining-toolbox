#ifndef FILTERNODE_H
#define FILTERNODE_H

#include "Node.hpp"

//Node that filters columns with user given column names
class FilterNode : public Node {
public:
    
    //Constructor
    FilterNode(std::string name);

    //Getter
    std::set<std::string> ColumnNames();
    //Setter
    void SetColumnNames(std::set<std::string> colNames);

    //Method for adding single column name
    void AddColumn(std::string colName);
    //Method for removing single column name
    void RemoveColName(std::string colName);

    void run() override;

protected:
    
    //Set of column names for columns that need to be removed
    std::set<std::string> columnNames;
};

#endif // FILTERNODE_H

///home/aleksandra/Documents/faks/7.semestar/RS/projekat1/RS012-data-mining-toolbox
