#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds
{
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{

		try {
			if (file == "") throw;
			std::fstream fileOpen(file);
			if (!fileOpen) throw;

			std::string temp, current, next;
			Utilities utils;
			size_t nPos{ 0u };
			bool more{ false };
			while (std::getline(fileOpen, temp)) {
				next = "";
				current = utils.extractToken(temp, nPos, more);
				if (more)
					next = utils.extractToken(temp, nPos, more);
				//using STL algorithm to push work stations into activeLine
				std::for_each(stations.begin(), stations.end(), [&](Workstation* currentWs) {
					if (currentWs->getItemName() == current) {
						std::for_each(stations.begin(), stations.end(), [&](Workstation* nextWs) {
							if (nextWs->getItemName() == next)
								currentWs->setNextStation(nextWs);
							});
						activeLine.push_back(currentWs);
					}
					});
			}
			m_firstStation = activeLine.front();
			m_cntCustomerOrder = pending.size();
		}
		catch (...) {
			throw("Error reading file");
		}



	}

	void LineManager::linkStations()
	{
		size_t i{ 0u };
		std::vector<Workstation*> tmpVec{ };
		tmpVec.push_back(m_firstStation);

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation*) {
			std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
				if (tmpVec[i]->getNextStation()) {
					if (tmpVec[i]->getNextStation()->getItemName() == ws->getItemName()) {
						tmpVec.push_back(ws);
						i++;
					}
				}
				});
			});
		if (!tmpVec.empty())
			activeLine = tmpVec;

	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t iteration = 0;


		os << "Line Manager Iteration: " << iteration + 1 << std::endl;
		if (!pending.empty())
		{
			(*m_firstStation).operator+=(std::move(pending.front()));
			pending.pop_front();
		}

		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
		{
			(*i)->fill(os);
		}

		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
		{
			(*i)->attemptToMoveOrder();
		}

		iteration++;

		//check if all orders have been processed
		if (pending.empty() && completed.size() + incomplete.size() == m_cntCustomerOrder)
			return true;

		return false;
	}

	void LineManager::display(std::ostream& os) const
	{
		std::vector<Workstation*>::const_iterator i;
		for (i = activeLine.begin(); i != activeLine.end(); i++)
		{
			(*i)->display(os);
		}
	}
}