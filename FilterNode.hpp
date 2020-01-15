#ifndef FILTERNODE_H
#define FILTERNODE_H

#include "Node.hpp"

class FilterNode : public Node {
public:
    FilterNode(std::string name);

    std::set<std::string> ColumnNames();
    void SetColumnNames(std::set<std::string> colNames);

    void AddColumn(std::string colName);
    void RemoveColName(std::string colName);

    void run() override;

protected:
    std::set<std::string> columnNames;
};

#endif // FILTERNODE_H

///home/aleksandra/Documents/faks/7.semestar/RS/projekat1/RS012-data-mining-toolbox
