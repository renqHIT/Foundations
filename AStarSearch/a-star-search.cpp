#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue> 

using namespace std;

class CNode
{
	public:

		CNode() : xPos(0), yPos(0), travelCost(0) {}
		CNode(int x, int y) : xPos(x), yPos(y), travelCost(0) {}
		CNode(int x, int y, int cost) : xPos(x), yPos(y), travelCost(cost) {}

		inline CNode& operator=(const CNode& target)
		{
			if (*this != target)
			{
				xPos = target.xPos;
				yPos = target.yPos;
				travelCost = target.travelCost;
			}

			return *this;
		}

		inline bool operator==(const CNode& target) const
		{
			return xPos == target.xPos && yPos == target.yPos;
		}

		inline bool operator!=(const CNode& target) const
		{
			return !(*this == target);
		}

		inline bool operator<(const CNode& target) const
		{
			return target.travelCost < travelCost;
		}

		int xPos, yPos, travelCost;
};

class CPath
{
	public:

		typedef vector<CNode> nodeList;

		nodeList Find(const CNode& startNode, const CNode& endNode, int mapArray[][20])
		{
			nodeList finalPath, openList, closedList;

			finalPath.push_back(startNode);
			openList.push_back(startNode);
			closedList.push_back(startNode);

			while (!openList.empty())
			{
				// Check each node in the open list
				for (size_t i = 0; i < openList.size(); ++i)
				{
					if (openList[i].xPos == endNode.xPos && openList[i].yPos == endNode.yPos)
						return finalPath;

					priority_queue<CNode> nodeQueue;

					// Get surrounding nodes
					for (int x = -1; x <= 1; ++x)
					{
						for (int y = -1; y <= 1; ++y)
						{
							const int current_x = openList[i].xPos + x;
							const int current_y = openList[i].yPos + y;

							bool alreadyCheckedNode = false;
							for (size_t i = 0; i < closedList.size(); ++i)
							{
								if (current_x == closedList[i].xPos && current_y == closedList[i].yPos)
								{
									alreadyCheckedNode = true;
									break;
								}
							}

							if (alreadyCheckedNode)
								continue;

							// Ignore current coordinate and don't go out of array scope
							if (current_x < 0 || current_x > 20 || current_y < 0 ||current_y > 20 || (openList[i].xPos == current_x && openList[i].yPos == current_y))
								continue;

							// Ignore walls
							if (mapArray[current_x][current_y] == '#')
								continue;

							const int xNodeDifference = abs(current_x - (openList[i].xPos));
							const int yNodeDifference = abs(current_y - (openList[i].yPos));            

							// Diagonal?
							const int direction = xNodeDifference == 1 && yNodeDifference == 1 ? 14 : 10;

							const int xDistance = abs(current_x - endNode.xPos);
							const int yDistance = abs(current_y - endNode.yPos);
							int heuristic = 10 * (xDistance + yDistance);

							nodeQueue.push(CNode(current_x, current_y, heuristic));
						}
					}

					if (!nodeQueue.empty())
					{
						// Add the nearest node
						openList.push_back(nodeQueue.top());
						finalPath.push_back(nodeQueue.top());

						// Put into closed list
						while (!nodeQueue.empty())
						{
							closedList.push_back(nodeQueue.top());
							nodeQueue.pop();
						}
					}
				}
			}

			return finalPath;
		}
};

int mapArray[20][20] =
{
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
	{ '#', 'A', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', '#' },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },

};

int main(int argc, char** argv)
{
	CNode start, end;

	for (int width = 0; width < 20; ++width)
	{
		for (int height = 0; height < 20; ++height)
		{
			if (mapArray[width][height] == 'A')
			{
				start.xPos = width;
				start.yPos = height;
			}
			else if (mapArray[width][height] == 'B')
			{
				end.xPos = width;
				end.yPos = height;
			}
		}
	}

	CPath pathFinder;
	CPath::nodeList n = pathFinder.Find(start, end, mapArray);

	for (int i = 0; i < n.size(); ++i)
		if (mapArray[n[i].xPos][n[i].yPos] != 'A' && mapArray[n[i].xPos][n[i].yPos] != 'B')
			mapArray[n[i].xPos][n[i].yPos] = '*';

	for (int height = 0; height < 20; ++height)
	{
		for (int width = 0; width < 20; ++width)
		{
			if (width % 20 == 0)
				cout << endl;

			cout << (char)mapArray[height][width] << " ";
		}
	}

	cin.get();

	return 0;
}
