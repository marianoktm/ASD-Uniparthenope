//
// Created by apont on 1/11/2023.
//

#include <vector>
#include <iostream>

class AssemblyLine {
public:
    std::vector<int> assembly_time_a;
    std::vector<int> transfer_time_t;
    int entry_time_e;
    int exit_time_x;

    AssemblyLine(const std::vector<int> &mountTimeA, const std::vector<int> &transferTimeT, int entryTimeE, int exitTimeX):
            assembly_time_a(mountTimeA), transfer_time_t(transferTimeT), entry_time_e(entryTimeE), exit_time_x(exitTimeX) {}
};

class AssemblyLineSolver {
private:
    std::vector<AssemblyLine> lines;

    std::vector<std::pair<int,int>> f;
    std::vector<std::pair<int,int>> l;

    int solution_f = 0;
    int solution_l = 0;

public:
    AssemblyLineSolver(const std::vector<AssemblyLine> &lines): lines(lines) {}

    void fastest_way();
    void print_solution();

    void solve_and_print();
};

void AssemblyLineSolver::fastest_way() {
    AssemblyLine line_S1 = lines.at(0);
    AssemblyLine line_S2 = lines.at(1);

    f.resize(lines.size());
    l.resize(lines.size());

    f.assign(lines.size() ,{0,0});
    l.assign(lines.size() ,{0,0});

    f.at(0).first = line_S1.entry_time_e + line_S1.assembly_time_a.at(0);
    f.at(0).second = line_S2.entry_time_e + line_S2.assembly_time_a.at(0);

    l.at(0).first = 1;
    l.at(0).second = 2;

    for (int j = 1; j < lines.size(); j++) {
        if (
                (f.at(j-1).first + line_S1.assembly_time_a.at(j))
                <=
                (f.at(j-1).second + line_S2.transfer_time_t.at(j-1) + line_S2.assembly_time_a.at(j))
        ) {
            f.at(j).first = f.at(j-1).first + line_S1.assembly_time_a.at(j);
            l.at(j).first = 1;
        }
        else {
            f.at(j).first = f.at(j-1).second + line_S2.transfer_time_t.at(j-1) + line_S2.assembly_time_a.at(j);
            l.at(j).first = 2;
        }

        if (
                (f.at(j-1).second + line_S2.assembly_time_a.at(j))
                <=
                (f.at(j-1).first + line_S1.transfer_time_t.at(j-1) + line_S1.assembly_time_a.at(j))
        ) {
            f.at(j).second = f.at(j-1).second + line_S2.assembly_time_a.at(j);
            l.at(j).second = 2;
        }
        else {
            f.at(j).second = f.at(j-1).first + line_S1.transfer_time_t.at(j-1) + line_S1.assembly_time_a.at(j);
            l.at(j).second = 1;
        }
    }

    int f1_total = f.at(f.size()-1).first + line_S1.exit_time_x;
    int f2_total = f.at(f.size()-1).second + line_S2.exit_time_x;
    if (f1_total <= f2_total) {
        solution_f = f1_total;
        solution_l = 1;
    }
    else {
        solution_f = f2_total;
        solution_l = 2;
    }
}

void AssemblyLineSolver::print_solution() {
    for (int i = 0; i < lines.size(); i++) {
        if (solution_l == 1) {
            std::cout << l.at(i).first << " -> ";
        }
        else {
            std::cout << l.at(i).second << " -> ";
        }
    }
    std::cout << std::endl << "With total price of: " << solution_f << std::endl;
}

void AssemblyLineSolver::solve_and_print() {
    this->fastest_way();
    this->print_solution();
}

int main() {
    std::vector<AssemblyLine> lines;
    AssemblyLine line0({7,9,3,4,8,4}, {2,3,1,1,4}, 2, 3);
    AssemblyLine line1({8,5,6,4,5,7}, {2,1,2,2,1}, 4, 2);

    lines.push_back(line0);
    lines.push_back(line1);

    AssemblyLineSolver solver(lines);
    solver.solve_and_print();

    return 0;
}
