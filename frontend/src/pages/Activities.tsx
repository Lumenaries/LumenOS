import Header from "../components/Header";
import ActivityCard from "../components/ActivityCard";
import {
  BaseballIcon,
  BasketballIcon,
  FootballIcon,
  SoccerIcon,
  TennisIcon,
  VolleyballIcon,
} from "../components/ActivityIcons";

function Activities() {
  return (
    <>
      <Header>Lumenaries</Header>
      <div class="flex justify-center font-medium">
        <div class="grid grid-cols-2 gap-x-10 gap-y-10 sm:grid-cols-3">
          <ActivityCard name="Football" icon={<FootballIcon />} />
          <ActivityCard name="Soccer" icon={<SoccerIcon />} />
          <ActivityCard name="Baseball" icon={<BaseballIcon />} />
          <ActivityCard name="Basketball" icon={<BasketballIcon />} />
          <ActivityCard name="Tennis" icon={<TennisIcon />} />
          <ActivityCard name="Volleyball" icon={<VolleyballIcon />} />
        </div>
      </div>
    </>
  );
}

export default Activities;
