import Header from "../components/Header";
import SportCard from "../components/SportCard";
import {
  BaseballIcon,
  BasketballIcon,
  FootballIcon,
  SoccerIcon,
  TennisIcon,
  VolleyballIcon,
} from "../components/SportIcons";

function Games() {
  return (
    <>
      <Header>Lumenaries</Header>
      <div class="flex justify-center font-medium">
        <div class="grid grid-cols-2 gap-x-10 gap-y-10 sm:grid-cols-3">
          <SportCard name="Baseball" icon={<BaseballIcon />} />
          <SportCard name="Basketball" icon={<BasketballIcon />} />
          <SportCard name="Football" icon={<FootballIcon />} />
          <SportCard name="Soccer" icon={<SoccerIcon />} />
          <SportCard name="Tennis" icon={<TennisIcon />} />
          <SportCard name="Volleyball" icon={<VolleyballIcon />} />
        </div>
      </div>
    </>
  );
}

export default Games;
