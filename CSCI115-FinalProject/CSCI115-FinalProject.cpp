#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

class Matrix {
private:
    std::vector<std::vector<char>> data;

public:
    Matrix(const std::string& filename) {
        loadFromFile(filename);
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }

        char cell;
        while (file >> cell) {
            data.emplace_back(std::initializer_list<char>{cell});
        }
    }

    void display() const {
        for (const auto& row : data) {
            for (char cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    char getValue(int row, int col) const {
        return data[row][col];
    }

    void setValue(int row, int col, char value) {
        data[row][col] = value;
    }

    int getRows() const {
        return data.size();
    }

    int getCols() const {
        return data.empty() ? 0 : data[0].size();
    }
};

class Player {
private:
    int row;
    int col;

public:
    Player(int startRow, int startCol) : row(startRow), col(startCol) {}

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    void move(int newRow, int newCol) {
        row = newRow;
        col = newCol;
    }
};

class Enemy {
private:
    int row;
    int col;

public:
    Enemy(int startRow, int startCol) : row(startRow), col(startCol) {}

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    void moveTowards(const Player& player, const Matrix& matrix) {
        // Implement the shortest path algorithm here to move the enemy towards the player
        // For simplicity, let's just move towards the player without any pathfinding logic
        if (row < player.getRow() && matrix.getValue(row + 1, col) != '#') {
            row++;
        }
        else if (row > player.getRow() && matrix.getValue(row - 1, col) != '#') {
            row--;
        }
        else if (col < player.getCol() && matrix.getValue(row, col + 1) != '#') {
            col++;
        }
        else if (col > player.getCol() && matrix.getValue(row, col - 1) != '#') {
            col--;
        }
    }
};

class Map {
private:
    Matrix matrix;
    Player player;
    Enemy enemy;

public:
    Map(const std::string& filename) : matrix(filename), player(1, 1), enemy(1, matrix.getCols() - 2) {}

    void display() const {
        matrix.display();
    }

    void movePlayer(char direction) {
        int newRow = player.getRow();
        int newCol = player.getCol();

        switch (direction) {
        case 'W':
            newRow--;
            break;
        case 'S':
            newRow++;
            break;
        case 'A':
            newCol--;
            break;
        case 'D':
            newCol++;
            break;
        default:
            std::cerr << "Invalid direction: " << direction << std::endl;
            return;
        }

        if (isValidMove(newRow, newCol)) {
            player.move(newRow, newCol);
        }
    }

    void updateEnemy() {
        enemy.moveTowards(player, matrix);
    }

private:
    bool isValidMove(int row, int col) const {
        return row >= 0 && row < matrix.getRows() && col >= 0 && col < matrix.getCols() &&
            matrix.getValue(row, col) != '#';
    }
};

int main() {
    // Assuming 'map.txt' contains a valid map
    Map gameMap("map.txt");

    // Display the initial state of the map
    gameMap.display();

    // Example: Move player 'W' (Up), 'A' (Left), 'S' (Down), 'D' (Right)
    gameMap.movePlayer('W');
    gameMap.display();

    // Update enemy position towards the player
    gameMap.updateEnemy();
    gameMap.display();

    // Continue testing and interacting with the game as needed

    return 0;
}
