#pragma once

#include "arac_model/AracModel.hpp"
#include "kulman_controller/LinearOpenLoopController.hpp"
#include <vector>

namespace kuco {

using Model = kuco::AracModel;
class AracOLController : public LinearOpenLoopController<Model>
{
 public:
  // Constructor.
//  aracController(kuco::State& state);
  AracOLController(Model& model);

  // Destructor.
  virtual ~AracOLController();

  // Init
  virtual void initilize() override;

  // Parameters init
  virtual void readParameters() override;

 protected:

  virtual void getState() override;

  virtual void setActuatorCommand() override;

  // Wheel yaricapi
  double rWheel_ ;
  // Wheel uzakligi
  double lWheel_ ;
};

} /* kuco adligi*/
