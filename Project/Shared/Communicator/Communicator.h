#ifndef Communicator_H
#define Communicator_H

#include <QEvent>
#include <QObject>
#include <QUuid>
#include <optional>
#include <set>

// test neuralNetInfo
#include "Shared/NeuralNetwork/Defines.h"
// test

namespace Shared {
namespace Communicator {
class IEvent : public QEvent {
public:
  virtual IEvent *copy() const = 0;

protected:
  IEvent(const QEvent::Type eventType) : QEvent(eventType) {}
};

template <class EventType> class Event : public IEvent {
public:
  virtual ~Event() {}

  static QEvent::Type staticType() {
    static QEvent::Type sType =
        static_cast<QEvent::Type>(QEvent::registerEventType());
    return sType;
  }

  IEvent *copy() const {
    return new EventType(*static_cast<const EventType *>(this));
  }

protected:
  Event() : IEvent(staticType()) {}
};

struct EvNeuralNetCreate : public Event<EvNeuralNetCreate> {
  EvNeuralNetCreate(const std::vector<unsigned long> &layerSizes,
                    const double learningRate,
                    const std::optional<unsigned> seed,
                    const QUuid &neuralNetId)
      : Event<EvNeuralNetCreate>(), layerSizes(layerSizes),
        learningRate(learningRate), seed(seed), networkId(neuralNetId) {}

  const std::vector<unsigned long> layerSizes;
  const double learningRate;
  const std::optional<unsigned> seed;
  const QUuid networkId;
};

struct EvNeuralNetCreateResponse : public Event<EvNeuralNetCreateResponse> {
  EvNeuralNetCreateResponse(const std::optional<QUuid> &neuralNetId)
      : Event<EvNeuralNetCreateResponse>(), networkId(neuralNetId) {}

  const std::optional<const QUuid> networkId;
};

struct EvNeuralNetRun : public Event<EvNeuralNetRun> {
  EvNeuralNetRun(const QUuid &neuralNetId, const ulong learningIterations,
                 const ulong testingIterations,
                 const std::optional<ulong> dataSeed = std::nullopt)
      : Event<EvNeuralNetRun>(), networkId(neuralNetId),
        learningIterations(learningIterations),
        testingIterations(testingIterations), dataSeed(dataSeed) {}

  const QUuid networkId;
  const ulong learningIterations;
  const ulong testingIterations;
  const std::optional<ulong> dataSeed;
};

class EvNeuralNetRunInfo : public Event<EvNeuralNetRunInfo> {
public:
  EvNeuralNetRunInfo(const QUuid &neuralNetId,
                     const Shared::NodeNetwork::NeuralNetworkData<double> &data)
      : Event<EvNeuralNetRunInfo>(), networkId(neuralNetId), networkData(data) {
  }

  const QUuid networkId;

  const Shared::NodeNetwork::NeuralNetworkData<double> networkData;
};

class Communicator : public QObject {
  Q_OBJECT

public:
  ~Communicator();

  static Communicator &instance();

  void connect(QObject *const receiver,
               const std::vector<IEvent::Type> &events);

  void postEvent(const IEvent *const event) const;
  // TODO: broadcast connect; create objectTypes as we have eventTypes, when
  // sending broadcast events, they are sent to all objects of a type instead
  // of a unique object.

private:
  Communicator();

  std::map<const IEvent::Type, std::set<QObject *>> mReceivers;
};

} // namespace Communicator
} // namespace Shared

#endif // Communicator_H
