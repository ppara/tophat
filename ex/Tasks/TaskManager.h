#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Util/Serialisable.hpp"
#include "TaskInterface.h"
#include "AbortTask.h"
#include "GotoTask.h"
#include "OrderedTask.h"
#include "TaskStats/TaskStats.hpp"
#include "GlideSolvers/GlidePolar.hpp"
#include "BaseTask/TaskProjection.h"
#include "TaskEvents.hpp"
#include "TaskBehaviour.hpp"


class Waypoints;
class TaskVisitor;

class TaskManager : public TaskInterface,
 public Serialisable
{
public:
  TaskManager(const TaskEvents &te,
              const TaskBehaviour &tb,
              GlidePolar &gp,
              const Waypoints &wps): 
    task_ordered(te,tb,wps.get_task_projection(),task_advance,gp),
    task_goto(te,tb,task_advance,gp),
    task_abort(te,tb,wps.get_task_projection(),task_advance,gp,wps),
    task_behaviour(tb)
  {
    set_mode(MODE_ORDERED);
  };

    virtual void setActiveTaskPoint(unsigned);

    virtual TaskPoint* getActiveTaskPoint();

  enum TaskMode_t {
    MODE_NULL=0,
    MODE_ORDERED,
    MODE_ABORT,
    MODE_GOTO
  };

  void abort();
  void resume();
  void do_goto(const Waypoint & wp);

#ifdef DO_PRINT
  virtual void print(const AIRCRAFT_STATE &location);
#endif

  virtual bool update(const AIRCRAFT_STATE &, const AIRCRAFT_STATE&);
  virtual bool update_idle(const AIRCRAFT_STATE &state);

  virtual const TaskStats& get_stats() const;

  bool append(OrderedTaskPoint *new_tp);
  bool insert(OrderedTaskPoint *new_tp, unsigned position);
  bool remove(unsigned position);
  bool check_task() const;

private:
  const TaskStats null_stats;

  TaskMode_t set_mode(const TaskMode_t mode);

  AbstractTask* active_task;

  TaskMode_t mode;


  /** @link aggregation */
  OrderedTask task_ordered;

  /** @link aggregation */
  GotoTask task_goto;
  
  /** @link aggregation */
  AbortTask task_abort;
  
  /** @link aggregation */
  TaskAdvance task_advance;
  
  const TaskBehaviour &task_behaviour;
  
  /** @link dependency */
  /*#  TaskEvents lnkTaskEvents; */

public:
  void Accept(BaseVisitor& visitor) const;
};
#endif //TASKMANAGER_H
