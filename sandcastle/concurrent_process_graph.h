/*!************************************************************
	Created	:	2016/03/17
	Intent	:		
		SceneGraphs are graphs that manages the execution order
    of job blocks. Think of them as a "level".
	Usage	:
		
    ##Preliminary use case here##
    ```
    ProcessGraphNode a;
    ProcessGraphNode b( ** jobs here ** );

    a.triggers(b);
    a.loadjob( ** jobs here ** );

    ProcessGraph graph(a);

    graph.start();
    ```

	Note	:
		Should ideally be serializable. Though that would be
    a longer-term plan
**************************************************************/
#ifndef concurrent_process_graph__
#define concurrent_process_graph__

#include "concurrent_dispatcher.h"
#include "include_std.h"

namespace Concurrent
{

  //the graph node, itself a job
  /*
    GRAPH IS CURRENTLY JUST A LIST.

    nextnode is done
  */
  class ProcessGraphNode : public Job
  {
  public:

    ProcessGraphNode(const SimpleDispatcher& work_unit = SimpleDispatcher());

    //no `execute` job since Job already has `Run`

    void AddJob(Job* job);
    void ClearJobs();

    void SetJobBlock(const SimpleDispatcher& work_unit);

    void SetNextNode(ProcessGraphNode* nextnode);

  private:

    virtual void JobDefinition() override;

    SimpleDispatcher m_jobs;
    ProcessGraphNode* m_nextnode = nullptr;
    //we got a problem, how would you want to handle many-to-1 connections?

  };

  //the main container
  class ProcessGraph
  {
  public:

    void Start(); //throws the job into the scheduler

  private:
  };

} //namespace Concurrent

#endif // concurrent_process_graph__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


