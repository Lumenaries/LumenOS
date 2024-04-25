import {
  createContext,
  createEffect,
  createSignal,
  onCleanup,
  useContext,
} from "solid-js";

const EventContext = createContext();

function EventProvider(props) {
  const [eventData, setEventData] = createSignal(null);

  createEffect(() => {
    const eventSource = new EventSource("/api/v1/event");

    eventSource.onmessage = (event) => {
      const sportData = JSON.parse(event.data);
      setEventData({ ...sportData });
    };

    onCleanup(() => {
      eventSource.close();
    });
  });

  return (
    <EventContext.Provider value={eventData}>
      {props.children}
    </EventContext.Provider>
  );
}

function useEvent() {
  return useContext(EventContext);
}

export { EventProvider, useEvent };
