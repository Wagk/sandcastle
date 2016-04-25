/*!************************************************************
	Created	:	2016/03/20
	Note	:
		
**************************************************************/
#include "concurrent_process_graph.h"

namespace Concurrent
{

  /*!************************************************************

  **************************************************************/
  ProcessGraphNode::ProcessGraphNode(const SimpleDispatcher& work_unit /*= SimpleDispatcher()*/)
    : m_jobs(work_unit)
  {

  }

  /*!************************************************************

  **************************************************************/
  void ProcessGraphNode::ClearJobs()
  {
    m_jobs.Clear();
  }

  /*!************************************************************

  **************************************************************/
  void ProcessGraphNode::SetJobBlock(const SimpleDispatcher& work_unit)
  {
    m_jobs = work_unit;
  }

  /*!************************************************************

  **************************************************************/
  void ProcessGraphNode::SetNextNode(ProcessGraphNode* nextnode)
  {
    m_nextnode = nextnode;
  }

  /*!************************************************************

  **************************************************************/
  void ProcessGraphNode::JobDefinition()
  {
    //this will execute and wait for all the jobs in the block
    m_jobs.Run();

    //the important bit is that m_nextnode will only get scheduled
    //once m_jobs has *completely* finished execution
    if (m_nextnode != nullptr)
    {
      m_nextnode->Schedule();
    }
  }

}


/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
