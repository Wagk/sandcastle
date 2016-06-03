/*******************************************************************************
  _____         _   _ _____   _____           _____ _______ _      ______
 / ____|  /\   | \ | |  __ \ / ____|   /\    / ____|__   __| |    |  ____|
| (___   /  \  |  \| | |  | | |       /  \  | (___    | |  | |    | |__
 \___ \ / /\ \ | . ` | |  | | |      / /\ \  \___ \   | |  | |    |  __|
 ____) / ____ \| |\  | |__| | |____ / ____ \ ____) |  | |  | |____| |____
|_____/_/    \_\_| \_|_____/ \_____/_/    \_\_____/   |_|  |______|______|

================================================================================
TODO:
  - Figure out how each module/ship/piece interacts with each other
    - Basically the gameplay. Stats? d20? Someone still has to define the rules
    - Probably just a lot of status inflictions. Need to be able to support
      physics and stuff in the future too, but probably no health or stuff like
      that, just pure strings

  - Figure out a painless way to generate metadata, which will painlessly 
    generate serialization data

  - Figure out how multithreading enters all these to speed up the program and
    make our lives hell.

  - Determine a way to set up jobs so we can somewhat finalize how we want to
    approach the scheduler/lockless queue problem.

  - Figure out how to define game state in terms of job blocks.
  - Figure out how to make workers, when blocking for a job, work on jobs,
    allowing Sandcastle to run on even a single thread
================================================================================

  We're going for the minimum viable  product (MVP) here, so fuck efficiency
  and go for something simple first. The trick is to engineer them in a way
  that we can make them more complicated later (also less dependent on each
  other)

*******************************************************************************/
#include <iostream>

#include "sandcastle.h"
#include "testing_concurrency.h"

#include "sandcastle/utility_filesystem.h"
#include "sandcastle/concurrent_scheduler.h"

#include "sandcastle_graphics/testing_graphics.h"


bool run_simulation = true;


int main(int argc, char* argv[])
{

  /*
    So the expected workflow for main(), in a multicore context, would be:

    SceneGraph graph; //the initial stage, basically splash screen.

    graph.run(); //deposits a single job that will spawn other jobs

    BecomeWorker(); //turns into a graphics bitch

  */

  /*
    The way I'm visualising how `graph.run()` goes is something like this:

    graph.run() creates a job and tosses it into a hungry core.
    that job spawns more jobs, which also get tossed into a hungry core.
    those jobs might spawn yet more jobs, but ultimately when they resolve
    it'll all come back to graph.run().

    While graph.run() is waiting for results it will be blocking, and while
    blocking, be processing jobs itself, so that no core is ever truly asleep.

    Once done graph.run() will, thanks to its graph data, know which batch
    of jobs to do next. Before it ends execution (remember it's a function and
    must eventually terminate), it will create another job and toss it into the
    burning core furnaces. That job will spawn a bunch of other jobs, much like
    graph.run(), and, like graph.run(), will manifest the next instruction set
    and toss it into the queue before terminating itself.

    It's assumed that the graph will know when it will end, and some will create
    some job whose job is to determine which graph to start next.

    I assume that's where most of the switching logic goes.
  */

  /*
    Don't forget that hazardpointers only really care about the number of 
    threads. Create as many queues as you want. We're fixing the number of
    threads running anyway.

    The only problem we will face is if we decide to oversubscribe and create
    even more threads, say, for resource loading, which must push into some
    global lockfree queue visible to people.

    We can have coarse-grained locked queues for that eventuality, as one way to
    handle it.

    We can also make it possible for a job to "detach", which mean we don't wait
    for it, and let a thread just deal with it.
  */

  Testing::Graphics::GraphicsTest();


  //DO NOT EXECUTE JOBS ABOVE HERE
  //DO NOT EXECUTE JOBS ABOVE HERE
  //DO NOT EXECUTE JOBS ABOVE HERE
  Interface::Singleton::Get<Concurrent::Scheduler>().Init();
  //ONLY EXECUTE JOBS BELOW HERE
  //ONLY EXECUTE JOBS BELOW HERE
  //ONLY EXECUTE JOBS BELOW HERE

  Testing::TestJob tjob;
  Interface::Singleton::Get<Concurrent::Scheduler>().AddJob(&tjob);

  Interface::Singleton::Get<Concurrent::Scheduler>().Run();

  while (1); //otherwise the threads will cry and we crash

}